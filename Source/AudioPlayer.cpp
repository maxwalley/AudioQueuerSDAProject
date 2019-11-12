/*
  ==============================================================================

    AudioPlayer.cpp
    Created: 3 Nov 2019 1:00:25pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayer.h"

//==============================================================================
AudioPlayer::AudioPlayer() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), playButton("Play"), pauseButton("Pause"), stopButton("Stop"), openFileButton("Open File"), timerCount(1),  waveform(audioFormatManager), transform(fftOrder), inputIndex(0), arrayPushingFinished(false), spectogram(Image::RGB, 512, 512, true)
{
    setSize (812, 512);
    
    audioFormatManager.registerBasicFormats();
       
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setRange(0, 1);
    gainSlider.setValue(0.5);
    gainSlider.addListener(this);
    audioTransportSource.setGain(gainSlider.getValue());
       
    addAndMakeVisible(playButton);
    playButton.addListener(this);
    playButton.setClickingTogglesState(true);
    playButton.setToggleState(false, dontSendNotification);
       
    addAndMakeVisible(pauseButton);
    pauseButton.addListener(this);
    pauseButton.setClickingTogglesState(true);
    pauseButton.setToggleState(false, dontSendNotification);
       
    addAndMakeVisible(stopButton);
    stopButton.addListener(this);
    stopButton.setClickingTogglesState(true);
    stopButton.setToggleState(true, dontSendNotification);
       
    addAndMakeVisible(openFileButton);
    openFileButton.addListener(this);

    addAndMakeVisible(timeLabel);
    timeLabel.setText("0", dontSendNotification);
    
    addAndMakeVisible(waveform);
    
    transportState = stopped;
    pausePosition = 0;
    
    waveform.addMouseListener(this, false);
}

AudioPlayer::~AudioPlayer()
{
}

void AudioPlayer::paint (Graphics& g)
{
    playButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
    pauseButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
    stopButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
    
    g.drawImage(spectogram, 300, 0, 512, 512, 0, 0, 512, 512);
}

void AudioPlayer::paintOverChildren(Graphics& g)
{
    if(audioTransportSource.isPlaying() == true)
    {
        g.drawLine((audioTransportSource.getCurrentPosition()/waveform.getThumbnailLenght()) * 200, 200, ((audioTransportSource.getCurrentPosition()/waveform.getThumbnailLenght()) * 200), 350);
    }
}

void AudioPlayer::resized()
{
    gainSlider.setBounds(170, 0, 30, 150);
    openFileButton.setBounds(0, 0, 150, 50);
    playButton.setBounds(0, 50, 50, 50);
    pauseButton.setBounds(50, 50, 50, 50);
    stopButton.setBounds(100, 50, 50, 50);
    timeLabel.setBounds(0, 110, 150, 40);
    
    waveform.setBounds(0, 200, 200, 150);
}

void AudioPlayer::buttonClicked(Button* button)
{
    if(button == &openFileButton)
    {
        if(fileChooser.browseForFileToOpen() == true)
        {
            selectedFile = fileChooser.getResult();
            
            waveform.setSource(new FileInputSource(selectedFile));
            
            AudioFormatReader* audioFormatReader = audioFormatManager.createReaderFor(selectedFile);
            
            if(audioFormatReader != nullptr)
            {
                fileLoaded = true;
                
                std::unique_ptr<AudioFormatReaderSource> tempAudioFormatReaderSource (new AudioFormatReaderSource (audioFormatReader, true));
            
                audioTransportSource.setSource(tempAudioFormatReaderSource.get(), 0, nullptr, audioFormatReader->sampleRate, audioFormatReader->numChannels);
            
                audioFormatReaderSource.reset(tempAudioFormatReaderSource.release());
            }
            else
            {
                DBG("No readers for that file");
            }
        }
    }
    
    else if(button == &playButton)
    {
        if(transportState == stopped)
        {
            audioTransportSource.setPosition(0);
        }
        else if(transportState == paused)
        {
            audioTransportSource.setPosition(pausePosition);
        }
        audioTransportSource.start();
        Timer::startTimer(40);
        playButton.setEnabled(false);
        stopButton.setToggleState(false, dontSendNotification);
        stopButton.setEnabled(true);
        pauseButton.setToggleState(false, dontSendNotification);
        pauseButton.setEnabled(true);
        transportState = playing;
    }
    
    else if(button == &stopButton)
    {
        audioTransportSource.stop();
        Timer::stopTimer();
        stopButton.setEnabled(false);
        pauseButton.setToggleState(false, dontSendNotification);
        pauseButton.setEnabled(false);
        playButton.setToggleState(false, dontSendNotification);
        playButton.setEnabled(true);
        transportState = stopped;
    }
    
    else if (button == &pauseButton)
    {
        pausePosition = audioTransportSource.getCurrentPosition();
        audioTransportSource.stop();
        pauseButton.setEnabled(false);
        playButton.setToggleState(false, dontSendNotification);
        playButton.setEnabled(true);
        stopButton.setToggleState(false, dontSendNotification);
        stopButton.setEnabled(true);
        transportState = paused;
    }
    
}

void AudioPlayer::sliderValueChanged(Slider* slider)
{
    if(slider == &gainSlider)
    {
        audioTransportSource.setGain(gainSlider.getValue());
    }
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    audioTransportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::getNextAudioBlock(const AudioSourceChannelInfo &bufferToFill)
{
    if(audioFormatReaderSource.get() == nullptr)
    {
        bufferToFill.clearActiveBufferRegion();
    }
    else
    {
        audioTransportSource.getNextAudioBlock(bufferToFill);
        
        auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
        for (int i = 0; i < bufferToFill.numSamples; ++i)
        {
            fillInputArray(channelData[i]);
        }
    }
}

void AudioPlayer::releaseResources()
{
    audioTransportSource.releaseResources();
}

void AudioPlayer::timerCallback()
{
    if(timerCount == 25)
    {
        int64_t numMins = floor(audioTransportSource.getCurrentPosition() / 60);
        double numSecs = fmod(audioTransportSource.getCurrentPosition(), 60);
        double decPoint = fmod(numSecs, 1);
        int64_t numSecsInt = numSecs - decPoint;
    
        std::string numMinsString = std::to_string(numMins);
        std::string numSecsString = std::to_string(numSecsInt);
    
        std::string fullTime = numMinsString + ":" + numSecsString;
    
        //DBG("Time is: " << fullTime);
        
        timerCount = 0;
        
        const MessageManagerLock labelLock;
        timeLabel.setText(fullTime, dontSendNotification);
    }
    //const MessageManagerLock paintLock;
    if (arrayPushingFinished == true)
    {
        
        drawSpectogram();
        
        
        arrayPushingFinished = false;
        repaint();
    }
    //drawSpectogram();
    //arrayPushingFinished = false;
    //repaint();
    timerCount++;
}

void AudioPlayer::mouseDown(const MouseEvent &event)
{
    //Checks its in the waveform area
    if(event.originalComponent == &waveform && fileLoaded == true)
    {
        changeAudioPosition(event.getMouseDownX());
    }
}

void AudioPlayer::changeAudioPosition(int xAxis)
{
    int disFromStart = waveform.getThumbnailLenght() - xAxis;
    
    //This is wrong for some reason
    double percentOfWaveform = waveform.getThumbnailLenght()/100;
    double newClickPosOnWaveform = percentOfWaveform * disFromStart;
    double percentOfFile = audioTransportSource.getTotalLength()/100;
    
    double newPosOnFile = newClickPosOnWaveform * percentOfFile;
    
    audioTransportSource.setPosition(newPosOnFile);
    
    //audioTransportSource.setPosition((waveform.getThumbnailLenght()/100) * disFromStart) * (audioTransportSource.getTotalLength()/100));
}

void AudioPlayer::fillInputArray(float sample)
{
    //DBG("Array size: " << transformInputArray.size());
    if(transformInputArray.size() == fftSize)
    {
        if(arrayPushingFinished == false)
        {
            transformOutputArray.clear();
            transformOutputArray.addArray(transformInputArray);
            arrayPushingFinished = true;
        }
        transformInputArray.clear();
    }
    transformInputArray.add(sample);
}

void AudioPlayer::drawSpectogram()
{
    spectogram.moveImageSection (0, 0, 1, 0, spectogram.getWidth() - 1, spectogram.getHeight());
    
    float array[fftSize * 2];
    
    for(int index = 0; index < fftSize; index++)
    {
        //moves dynamic array into normal one for fft
        array[index] = transformOutputArray.getReference(index);
        //DBG("data in Array = " << array[index]);
    }
    
    auto rightHandEdge = spectogram.getWidth() - 1;
    auto imageHeight   = spectogram.getHeight();
    
    spectogram.moveImageSection (0, 0, 1, 0, rightHandEdge - 1, imageHeight);
    
    transform.performRealOnlyForwardTransform(array);

    auto maxLevel = FloatVectorOperations::findMinAndMax (array, fftSize/2);
    for (auto y = 1; y < imageHeight; ++y)
    {
        
        auto skewedProportionY = 1.0f - std::exp (std::log (y / (float) imageHeight) * 0.2f);
        
        auto fftDataIndex = jlimit (0, fftSize / 2, (int) (skewedProportionY * fftSize / 2));
        auto level = jmap (array[fftDataIndex], 0.0f, jmax (maxLevel.getEnd(), 1e-5f), 0.0f, 1.0f);
        
        spectogram.setPixelAt (rightHandEdge - 1, y, Colour::fromHSV (level, 1.0f, level, 1.0f));
    }
    

}
