/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav", true, true, nullptr), fileLoaded(false), timerCount(1), waveform(*player.getAudioFormatManager()), infoBox(*player.getAudioFormatManager()), menu(this)
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
    transformImage.timerTrigger();
    
    addAndMakeVisible(infoBox);
    infoBox.addActionListener(this);
    
    deviceManager.initialise(0, 2, nullptr, true);
    
    player.addActionListener(this);
    
    addAndMakeVisible(menu);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    player.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    if(player.isPlaying() == true)
    {
        player.getNextAudioBlock(bufferToFill);
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
    player.releaseResources();
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll(Colours::grey);
}


void MainComponent::resized()
{
    menu.setBounds(0, 0, getWidth(), 20);
    playerGUI.setBounds(450, 375, 200, 250);
    transformImage.setBounds(0, 425, 256, 256);
    waveform.setBounds(0, 250, 200, 150);
    table.setBounds(50, 50, 750, 300);
    infoBox.setBounds(850, 50, 200, 525);
}

//==============================================================================
StringArray MainComponent::getMenuBarNames()
{
    //List of menu titles
    const char* const names[] = { "File", "Audio", "Queue", 0 };
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    //File tab
    if(topLevelMenuIndex == 0)
    {
        menu.addItem(1, "Audio Preferences", true, false);
        menu.addItem(2, "Add File to Queue", true, false);
    }
    
    //Audio tab
    else if(topLevelMenuIndex == 1)
    {
        menu.addItem(1, "Play Queue", true, false);
        menu.addItem(2, "Pause", true, false);
        menu.addItem(3, "Stop", true, false);
    }
    
    //Queue tab
    else if(topLevelMenuIndex == 2)
    {
        menu.addItem(1, "Loop Queue", true, false);
        menu.addItem(2, "Shuffle Queue", true, false);
        menu.addItem(3, "Play Continuously", true, false);
    }
    
    return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    if(topLevelMenuIndex == 0)
    {
        if(menuItemID == 1)
        {
            selectorWindow = new ComponentWindow("Audio Preferences", Colours::grey, DocumentWindow::allButtons);
            selectorWindow->setSize(300, 200);
            selector = new AudioDeviceSelectorComponent(deviceManager, 0, 0, 0, 2, false, false, true, false);
            
            selector->setSize(selectorWindow->getWidth(), selectorWindow->getHeight());
            selectorWindow->setContentOwned(selector, true);
            selectorWindow->setVisible(true);
        }
        else if(menuItemID == 2)
        {
            addFile();
        }
    }
    
    else if(topLevelMenuIndex == 1)
    {
        if(menuItemID == 1)
        {
            playQueue();
        }
        
        else if(menuItemID == 2)
        {
            pauseAudio();
        }
        
        else if(menuItemID == 3)
        {
            stopAudio();
        }
    }
    
    else if(topLevelMenuIndex == 2)
    {
        if(menuItemID == 1)
        {
            table.changeQueueControlToggle(QueueControls::loopQueue);
        }
        
        else if(menuItemID == 2)
        {
            table.changeQueueControlToggle(QueueControls::shuffleQueue);
        }
        
        else if(menuItemID == 3)
        {
            table.changeQueueControlToggle(QueueControls::playContinuously);
        }
    }
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
        table.moveIndexToPlayOn();
        setUpPlayer();
    }
    
    else if(button == &playerGUI.lastButton)
    {
        table.moveIndexToPlayBack();
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
        if(table.isEmpty() != true)
        {
            table.startQueue();
            player.loadNewFile(table.getFileToPlay(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), true);
            waveform.set(new FileInputSource(*table.getFileToPlay()));
        }
    }
    if(table.isEmpty() != true)
    {
        playerGUI.audioPlayed();
        Timer:startTimer(100);
    }
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
        //Checks if a row is selected
        if(table.isRowSelected() == true)
        {
            //Sends the data from the selected row to the info box
            infoBox.changeData(table.getCurrentSelectedDataStruct());
        }
        else
        {
            infoBox.clear();
        }
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
    
    else if(message == "Queue finished")
    {
        stopAudio();
    }
    
    else if(message == "Break")
    {
        playerGUI.audioStopped();
    }
    
    else if(message == "Transport Finished")
    {
        table.moveIndexToPlayOn();
               
        setUpPlayer();
    }
    
    else if(message == "Play button on QueueItem pressed")
    {
        player.loadNewFile(table.getFileToPlay(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), false);
        waveform.set(new FileInputSource(*table.getFileToPlay()));
        Timer:startTimer(100);
        playerGUI.audioPlayed();
    }
    
    else if(message == "Stop Audio")
    {
        stopAudio();
    }
}

void MainComponent::setUpPlayer()
{
    if(table.getFileToPlay() == nullptr)
    {
        playerGUI.audioStopped();
        stopAudio();
    }
    else
    {
        player.loadNewFile(table.getFileToPlay(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), true);
        waveform.set(new FileInputSource(*table.getFileToPlay()));
    }
}
