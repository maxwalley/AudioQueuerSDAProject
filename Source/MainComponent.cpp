/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), timerCount(1), waveform(audioFormatManager), infoBox(audioFormatManager), menu(deviceManager)
{
    setSize (1100, 650);

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
    
    playerGUI.gainSlider.addListener(this);
    playerGUI.playPauseButton.addListener(this);
    playerGUI.stopButton.addListener(this);
    playerGUI.nextButton.addListener(this);
    playerGUI.lastButton.addListener(this);
    table.queueControls.openFileButton.addListener(this);
    
    addAndMakeVisible(playerGUI);
    playerGUI.setButtonEnabled(&playerGUI.playPauseButton, false);
    
    
    addAndMakeVisible(waveform);
    waveform.addMouseListener(this, false);
    
    addAndMakeVisible(table);
    table.addActionListener(this);
    
    addAndMakeVisible(transformImage);
    
    addAndMakeVisible(infoBox);
    infoBox.addActionListener(this);
    
    menu.addActionListener(this);
    
    deviceManager.initialise(0, 2, nullptr, true);
    
    player.addActionListener(this);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player.transport.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    if(player.transport.isPlaying() == true)
    {
        player.transport.getNextAudioBlock(bufferToFill);
        player.stopPointReached();
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
    player.transport.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll(Colours::grey);
}


void MainComponent::resized()
{
    playerGUI.setBounds(450, 375, 200, 250);
    transformImage.setBounds(0, 425, 256, 256);
    waveform.setBounds(0, 250, 200, 150);
    table.setBounds(50, 50, 750, 300);
    infoBox.setBounds(850, 50, 200, 525);
}

void MainComponent::buttonClicked(Button* button)
{
    if(button == &table.queueControls.openFileButton)
    {
        addFile();
        playerGUI.setButtonEnabled(&playerGUI.playPauseButton, true);
    }
    
    else if(button == &playerGUI.playPauseButton)
    {
        if(player.isPlaying() == false)
        {
            playQueue();
        }
        else if(player.isPlaying() == true)
        {
            pauseAudio();
        }
        
    }
    
    else if(button == &playerGUI.stopButton)
    {
        stopAudio();
    }
    
    else if(button == &playerGUI.nextButton)
    {
        table.moveTransportOn();
        setUpPlayer();
    }
    
    else if(button == &playerGUI.lastButton)
    {
        table.moveTransportBack();
        setUpPlayer();
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
    if(player.isPaused() == true)
    {
        player.playFromPause();
    }
    else
    {
        table.startQueue();
        player.loadNewFile(table.getCurrentPlayingFile(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), true);
        waveform.set(new FileInputSource(*table.getCurrentPlayingFile()));
    }
    transformImage.timerTrigger();
    playerGUI.audioPlayed();
    Timer:startTimer(100);
}

void MainComponent::pauseAudio()
{
    //checks a file is playing
    if(player.isPlaying() == true)
    {
        player.pause();
        playerGUI.audioPaused();
    }
}

void MainComponent::stopAudio()
{
    table.reset();
    player.stop();
    Timer::stopTimer();
    playerGUI.audioStopped();
    waveform.clear();
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if(slider == &playerGUI.gainSlider)
    {
        player.setGain(playerGUI.gainSlider.getValue());
    }
}

void MainComponent::timerCallback()
{
    playerGUI.changeTime(player.getTransportPosition());
    
    if(player.isPlaying() == true)
    {
        waveform.moveTransportLine((player.getTransportPosition()/player.getTransportLengthInSeconds()) * 200);
    }
}

void MainComponent::mouseDown(const MouseEvent &event)
{
    //Checks its in the waveform area
    if(event.originalComponent == &waveform)
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
    player.setTransportPosition(percentageInTrack);
}

void MainComponent::actionListenerCallback(const String &message)
{
    //Called if a new row is selected
    if(message == "Selected Item Changed")
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
    
    else if(message == "Delete button pressed")
    {
        table.deleteSelectedItem();
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
    
    else if(message == "Queue finished")
    {
        stopAudio();
    }
    
    else if(message == "Loop Queue Clicked")
    {
        table.changeQueueControlToggle(1);
    }
    
    else if(message == "Shuffle Queue Clicked")
    {
        table.changeQueueControlToggle(2);
    }
    
    else if(message == "Continous Control Clicked")
    {
        table.changeQueueControlToggle(3);
    }
    
    else if(message == "Break")
    {
        playerGUI.audioStopped();
    }
    
    else if(message == "Transport Finished")
    {
        table.moveTransportOn();
               
        setUpPlayer();
    }
    
    else if(message == "Play button on QueueItem pressed")
    {
        player.loadNewFile(table.getCurrentPlayingFile(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), false);
        waveform.set(new FileInputSource(*table.getCurrentPlayingFile()));
    }
}

void MainComponent::setUpPlayer()
{
    if(table.getCurrentPlayingFile() == nullptr)
    {
        playerGUI.audioStopped();
        stopAudio();
    }
    else
    {
        player.loadNewFile(table.getCurrentPlayingFile(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), true);
        waveform.set(new FileInputSource(*table.getCurrentPlayingFile()));
    }
}
