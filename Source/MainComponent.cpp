/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), timerCount(1), waveform(audioFormatManager), selectedItem(-2)
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
       
    table.transport.setGain(playerGUI.gainSlider.getValue());
    
    addAndMakeVisible(playTypeCombo);
    playTypeCombo.addItem("Play Selected", 1);
    playTypeCombo.addItem("Play Playlist", 2);
    playTypeCombo.setSelectedId(2);
    
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
    table.addActionListener(this);
    
    addAndMakeVisible(transformImage);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    table.transport.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    if(table.itemPlaying() == true)
    {
        table.transport.getNextAudioBlock(bufferToFill);
    
        const MessageManagerLock stopPointLock;
        table.stopPointReached();
    }
    else
    {
        //Clears buffer if nothing is playing
        bufferToFill.clearActiveBufferRegion();
    }
    
    //FFT
    auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
    for (int i = 0; i < bufferToFill.numSamples; ++i)
    {
        transformImage.fillInputArray(channelData[i]);
    }
}

void MainComponent::releaseResources()
{
    table.transport.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    
}

void MainComponent::paintOverChildren(Graphics& g)
{
    /*if(table.transport.isPlaying() == true)
    {
        g.drawLine((table.transport.getCurrentPosition()/waveform.getThumbnailLenght()) * 200, 200, ((table.transport.getCurrentPosition()/waveform.getThumbnailLenght()) * 200), 350);
    }*/
}

void MainComponent::resized()
{
    playTypeCombo.setBounds(400, 400, 200, 30);
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
            table.addNewItem(&selectedFile);
        }
    }
    
    else if(button == &playerGUI.playButton)
    {
        if(transportState == stopped)
        {
            table.transport.setPosition(0);
        }
        else if(transportState == paused)
        {
            table.transport.setPosition(pausePosition);
        }
        table.startQueue();
        Timer::startTimer(100);
        transformImage.timerTrigger();
        playerGUI.audioPlayed();
        transportState = playing;
    }
    
    else if(button == &playerGUI.stopButton)
    {
        table.transport.stop();
        Timer::stopTimer();
        playerGUI.audioStopped();
        transportState = stopped;
    }
    
    else if (button == &playerGUI.pauseButton)
    {
        pausePosition = table.transport.getCurrentPosition();
        table.transport.stop();
        playerGUI.audioPaused();
        transportState = paused;
    }
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if(slider == &playerGUI.gainSlider)
    {
        table.transport.setGain(playerGUI.gainSlider.getValue());
    }
}

void MainComponent::timerCallback()
{
    playerGUI.changeTime(table.transport.getCurrentPosition());
}

void MainComponent::mouseDown(const MouseEvent &event)
{
    //Checks its in the waveform area
    if(event.originalComponent == &waveform /*&& fileLoaded == true*/)
    {
        DBG("Mouse clicked in waveform");
        changeAudioPosition(event.getMouseDownX());
    }
}

void MainComponent::changeAudioPosition(int xAxis)
{
    int disFromStart = waveform.getThumbnailLenght() - xAxis;
    
    //This is wrong for some reason
    double percentOfWaveform = waveform.getThumbnailLenght()/100;
    double newClickPosOnWaveform = percentOfWaveform * disFromStart;
    //double percentOfFile = audioTransportSource.getTotalLength()/100;
    
    //double newPosOnFile = newClickPosOnWaveform * percentOfFile;
    
    //audioTransportSource.setPosition(newPosOnFile);
    
    //audioTransportSource.setPosition((waveform.getThumbnailLenght()/100) * disFromStart) * (audioTransportSource.getTotalLength()/100));
}

void MainComponent::actionListenerCallback(const String &message)
{
    if(message == "Playing Item Changed")
    {
        //Retrieves the current file that is playing and sends it to the waveform
        File* currentFile = table.currentPlayingFile();
        waveform.set(new FileInputSource(*currentFile));
    }
}
