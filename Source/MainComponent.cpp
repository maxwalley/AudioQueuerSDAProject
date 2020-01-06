/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), timerCount(1), waveform(audioFormatManager), selectedItem(-2), infoBox(audioFormatManager), menu(&deviceManager)
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
    playerGUI.playButton.addListener(this);
    playerGUI.stopButton.addListener(this);
    playerGUI.nextButton.addListener(this);
    playerGUI.lastButton.addListener(this);
    table.queueControls.openFileButton.addListener(this);
    
    addAndMakeVisible(playerGUI);
    
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
    /*if(table.itemPlaying() == true)
    {
        table.transport.getNextAudioBlock(bufferToFill);
    
        const MessageManagerLock stopPointLock;
        table.stopPointReached();
    }
    else
    {
        //Clears buffer if nothing is playing
        bufferToFill.clearActiveBufferRegion();
    }*/
    
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

void MainComponent::paintOverChildren(Graphics& g)
{
    if(table.transport.isPlaying() == true)
    {
        g.drawLine((table.transport.getCurrentPosition()/table.transport.getLengthInSeconds()) * 200, 250, ((table.transport.getCurrentPosition()/table.transport.getLengthInSeconds()) * 200), 400);
    }
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
        playerGUI.setPlayButtonEnabled();
    }
    
    else if(button == &playerGUI.playButton)
    {
        if(playerGUI.playButton.getButtonState() == 0)
        {
            playQueue();
        }
        else if(playerGUI.playButton.getButtonState() == 1)
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
        table.moveTransportOn(true);
    }
    
    else if(button == &playerGUI.lastButton)
    {
        table.moveTransportBack();
    }
    
}

void MainComponent::addFile()
{
    //Move this into audio table fully
    if(fileChooser.browseForFileToOpen() == true)
    {
        selectedFile = fileChooser.getResult();
        table.addNewItem(&selectedFile);
    }
}

void MainComponent::playQueue()
{
    table.startQueue();
    player.loadNewFile(table.getCurrentPlayingFile());
    transformImage.timerTrigger();
    playerGUI.audioPlayed();
    Timer:startTimer(100);
}

void MainComponent::pauseAudio()
{
    //checks a file is playing
    if(table.transport.isPlaying() == true)
    {
        table.pauseAudio();
        playerGUI.audioPaused();
    }
}

void MainComponent::stopAudio()
{
    table.reset();
    Timer::stopTimer();
    playerGUI.audioStopped();
    waveform.clear();
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
    table.setTransportPosition(percentageInTrack);
}

void MainComponent::actionListenerCallback(const String &message)
{
    if(message == "Playing Item Changed")
    {
        //Retrieves the current file that is playing and sends it to the waveform
        File* currentFile = table.getCurrentPlayingFile();
        player.loadNewFile(currentFile);
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
    
    else if(message == "Break")
    {
        playerGUI.audioStopped();
    }
    
    else if(message == "Transport Finished")
    {
        table.moveTransportOn(false);
        
        //If the stream has finished
        if(table.getCurrentPlayingFile() == nullptr)
        {
            playerGUI.audioStopped();
        }
        else
        {
            player.loadNewFile(table.getCurrentPlayingFile());
        }
    }
}
