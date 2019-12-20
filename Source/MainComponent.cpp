/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), timerCount(1), waveform(audioFormatManager), selectedItem(-2), infoBox(audioFormatManager), menu(&deviceManager)
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
    
    addAndMakeVisible(infoBox);
    infoBox.addActionListener(this);
    
    menu.addActionListener(this);
    
    deviceManager.initialise(0, 2, nullptr, true);
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
    if(table.transport.isPlaying() == true)
    {
        g.drawLine((table.transport.getCurrentPosition()/waveform.getThumbnailLength()) * 200, 200, ((table.transport.getCurrentPosition()/waveform.getThumbnailLength()) * 200), 350);
    }
}

void MainComponent::resized()
{
    playTypeCombo.setBounds(400, 400, 200, 30);
    playerGUI.setBounds(0, 50, 200, 150);
    transformImage.setBounds(0, 450, 256, 256);
    waveform.setBounds(0, 250, 200, 150);
    table.setBounds(300, 50, 500, 300);
    infoBox.setBounds(850, 50, 200, 500);
}

void MainComponent::buttonClicked(Button* button)
{
    if(button == &playerGUI.openFileButton)
    {
        addFile();
    }
    
    else if(button == &playerGUI.playButton)
    {
        playQueue();
    }
    
    else if(button == &playerGUI.stopButton)
    {
        stopAudio();
    }
    
    else if (button == &playerGUI.pauseButton)
    {
        pauseAudio();
    }
}

void MainComponent::addFile()
{
    if(fileChooser.browseForFileToOpen() == true)
    {
        selectedFile = fileChooser.getResult();
        table.addNewItem(&selectedFile);
    }
}

void MainComponent::playQueue()
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

void MainComponent::pauseAudio()
{
    pausePosition = table.transport.getCurrentPosition();
    table.transport.stop();
    playerGUI.audioPaused();
    transportState = paused;
}

void MainComponent::stopAudio()
{
    table.transport.stop();
    Timer::stopTimer();
    playerGUI.audioStopped();
    transportState = stopped;
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
    repaint(0, 200, 200, 150);
}

void MainComponent::mouseDown(const MouseEvent &event)
{
    //Checks its in the waveform area
    if(event.originalComponent == &waveform /*&& fileLoaded == true*/)
    {
        changeAudioPosition(event.getMouseDownX());
    }
}

void MainComponent::changeAudioPosition(int xAxis)
{
    //Finds the percentage across the waveform component
    double percentageAcrossWaveform = (double(xAxis)/waveform.getWidth()) * 100.0;
    
    //Finds this point in the song
    double percentageInTrack = (waveform.getThumbnailLength()/100) * percentageAcrossWaveform;
    
    //Sets the new transport position
    table.setTransportPosition(percentageInTrack);
}

void MainComponent::actionListenerCallback(const String &message)
{
    if(message == "Playing Item Changed")
    {
        //Retrieves the current file that is playing and sends it to the waveform
        File* currentFile = table.getCurrentPlayingFile();
        waveform.set(new FileInputSource(*currentFile));
    }
    
    //Called if a new row is selected
    else if(message == "Selected Item Changed")
    {
        //Sends the data from the selected row to the info box
        infoBox.changeData(table.getCurrentSelectedDataStruct());
    }
    
    else if(message == "Loop button changed")
    {
        table.updateSelectedItemLoopToggle(infoBox.getLoopButtonState());
    }
    
    else if(message == "Number of loops changed")
    {
        table.updateSelectedItemNumLoops(infoBox.getNewNumLoops());
    }
    
    else if(message == "Add file")
    {
        addFile();
    }
    
    else if(message == "Play queue")
    {
        playQueue();
    }
    
    else if(message == "Pause audio")
    {
        pauseAudio();
    }
    
    else if(message == "Stop audio")
    {
        stopAudio();
    }
}
