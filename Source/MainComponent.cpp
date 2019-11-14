/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), playButton("Play"), pauseButton("Pause"), stopButton("Stop"), openFileButton("Open File"), timerCount(1), waveform(audioFormatManager)
{
    setSize (1100, 800);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                     [&] (bool granted) { if (granted)  setAudioChannels (2, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (0, 2);
    }
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
    
    addAndMakeVisible(transformImage);
    addAndMakeVisible(queueDisplay);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    audioTransportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
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
            transformImage.fillInputArray(channelData[i]);
        }
    }
}

void MainComponent::releaseResources()
{
    audioTransportSource.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    playButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
    pauseButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
    stopButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
}

void MainComponent::paintOverChildren(Graphics& g)
{
    if(audioTransportSource.isPlaying() == true)
    {
        g.drawLine((audioTransportSource.getCurrentPosition()/waveform.getThumbnailLenght()) * 200, 200, ((audioTransportSource.getCurrentPosition()/waveform.getThumbnailLenght()) * 200), 350);
    }
}

void MainComponent::resized()
{
    gainSlider.setBounds(170, 0, 30, 150);
    openFileButton.setBounds(0, 0, 150, 50);
    playButton.setBounds(0, 50, 50, 50);
    pauseButton.setBounds(50, 50, 50, 50);
    stopButton.setBounds(100, 50, 50, 50);
    timeLabel.setBounds(0, 110, 150, 40);
    transformImage.setBounds(0, 375, 256, 256);
    waveform.setBounds(0, 200, 200, 150);
    queueDisplay.setBounds(300, 0, 500, 300);
}

StringArray MainComponent::getMenuBarNames()
{
    const char* const names[] = { "File", 0 };
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    if (topLevelMenuIndex == 0)
    {
        menu.addItem(1, "Audio Prefrences", true, false);
        menu.addItem(2, "Open File", true, false);
    }
    
    return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    if(topLevelMenuIndex == 0)
    {
        if (menuItemID == 1)
        {
            DBG("AUDIO PREFS CLICKED");
        }
        else if (menuItemID == 2)
        {
            
        }
    }
}

void MainComponent::buttonClicked(Button* button)
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
        transformImage.timerTrigger();
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

void MainComponent::sliderValueChanged(Slider* slider)
{
    if(slider == &gainSlider)
    {
        audioTransportSource.setGain(gainSlider.getValue());
    }
}

void MainComponent::timerCallback()
{
    int64_t numMins = floor(audioTransportSource.getCurrentPosition() / 60);
    double numSecs = fmod(audioTransportSource.getCurrentPosition(), 60);
    double decPoint = fmod(numSecs, 1);
    int64_t numSecsInt = numSecs - decPoint;
    
    std::string numMinsString = std::to_string(numMins);
    std::string numSecsString = std::to_string(numSecsInt);
    
    std::string fullTime = numMinsString + ":" + numSecsString;
        
    const MessageManagerLock labelLock;
    timeLabel.setText(fullTime, dontSendNotification);
}

void MainComponent::mouseDown(const MouseEvent &event)
{
    //Checks its in the waveform area
    if(event.originalComponent == &waveform && fileLoaded == true)
    {
        changeAudioPosition(event.getMouseDownX());
    }
}

void MainComponent::changeAudioPosition(int xAxis)
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
