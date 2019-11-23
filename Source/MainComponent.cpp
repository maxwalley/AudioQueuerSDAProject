/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), timerCount(1), waveform(audioFormatManager)
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
       
    audioTransportSource.setGain(playerGUI.gainSlider.getValue());
    
    playerGUI.gainSlider.addListener(this);
    playerGUI.playButton.addListener(this);
    playerGUI.pauseButton.addListener(this);
    playerGUI.stopButton.addListener(this);
    playerGUI.openFileButton.addListener(this);
    
    addAndMakeVisible(playerGUI);
    addAndMakeVisible(waveform);
    
    transportState = stopped;
    pausePosition = 0;
    
    waveform.addMouseListener(this, false);
    
    addAndMakeVisible(table);
    
    addAndMakeVisible(transformImage);
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
    playerGUI.setBounds(0, 0, 200, 150);
    transformImage.setBounds(0, 375, 256, 256);
    waveform.setBounds(0, 200, 200, 150);
    table.setBounds(300, 0, 500, 300);
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
    if(button == &playerGUI.openFileButton)
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
            
            table.addNewItem(&selectedFile);
        }
    }
    
    else if(button == &playerGUI.playButton)
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
        playerGUI.audioPlayed();
        transportState = playing;
    }
    
    else if(button == &playerGUI.stopButton)
    {
        audioTransportSource.stop();
        Timer::stopTimer();
        playerGUI.audioStopped();
        transportState = stopped;
    }
    
    else if (button == &playerGUI.pauseButton)
    {
        pausePosition = audioTransportSource.getCurrentPosition();
        audioTransportSource.stop();
        playerGUI.audioPaused();
        transportState = paused;
    }
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if(slider == &playerGUI.gainSlider)
    {
        audioTransportSource.setGain(playerGUI.gainSlider.getValue());
    }
}

void MainComponent::timerCallback()
{
    playerGUI.changeTime(audioTransportSource.getCurrentPosition());
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
