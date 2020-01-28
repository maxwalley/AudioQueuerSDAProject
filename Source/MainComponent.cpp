/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent() : fileChooser("Pick a file", File(), "*.wav; *.mp3; *.m4a; *.flac", true, true, nullptr), fileLoaded(false), waveform(*player.getAudioFormatManager()), infoBox(*player.getAudioFormatManager()), menu(this)
{
    setSize (1100, 675);
    
    setAudioChannels(0, 2);

    playerGUI.gainSlider.addListener(this);
    playerGUI.playPauseButton.addListener(this);
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
    
    player.addActionListener(this);
    
    addAndMakeVisible(menu);
}

MainComponent::~MainComponent()
{
    //Deletes pointers to the colour selector windows
    backColSelWindow.deleteAndZero();
    waveColSelWindow.deleteAndZero();
    
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
    //Creates a read pointer at the start of the buffer
    auto* channelData = bufferToFill.buffer->getReadPointer (0, bufferToFill.startSample);
    
    //Iterates through the samples of the buffer
    for (int i = 0; i < bufferToFill.numSamples; ++i)
    {
        //Sends audio sample to the FFT for display
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
    transformImage.setBounds(0, 410, 256, 256);
    waveform.setBounds(0, 250, 200, 150);
    table.setBounds(50, 50, 750, 300);
    infoBox.setBounds(850, 50, 200, 525);
}

//==============================================================================
StringArray MainComponent::getMenuBarNames()
{
    //List of menu titles
    const char* const names[] = { "File", "Audio", "Queue", "Waveform", 0 };
    return StringArray (names);
}

PopupMenu MainComponent::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    //File tab
    if(topLevelMenuIndex == 0)
    {
        menu.addItem(1, "Add File", true, false);
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
    
    //Waveform tab
    else if(topLevelMenuIndex == 3)
    {
        menu.addItem(1, "Change Background Colour", true, false);
        menu.addItem(2, "Change Waveform Colour", true, false);
    }
    
    return menu;
}

void MainComponent::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    //File tab
    if(topLevelMenuIndex == 0)
    {
        //"Add File" option
        if(menuItemID == 1)
        {
            addFile();
        }
    }
    
    //Audio tab
    else if(topLevelMenuIndex == 1)
    {
        //"Play Queue" option
        if(menuItemID == 1)
        {
            playQueue();
        }
        
        //"Pause Queue" option
        else if(menuItemID == 2)
        {
            pauseAudio();
        }
        
        //"Stop Queue" option
        else if(menuItemID == 3)
        {
            stopAudio();
        }
    }
    
    //Queue tab
    else if(topLevelMenuIndex == 2)
    {
        //"Loop Queue" option
        if(menuItemID == 1)
        {
            table.changeQueueControlToggle(QueueControls::loopQueue);
        }
        
        //"Shuffle Queue" option
        else if(menuItemID == 2)
        {
            table.changeQueueControlToggle(QueueControls::shuffleQueue);
        }
        
        //"Play Continuously" option
        else if(menuItemID == 3)
        {
            table.changeQueueControlToggle(QueueControls::playContinuously);
        }
    }
    
    //Waveform tab
    else if(topLevelMenuIndex == 3)
    {
        //"Change Background Colour" option
        if(menuItemID == 1)
        {
            //Opens and initilises a new ColourSelectorWindow
            backColSelWindow = new ColourSelectorWindow("Background Colour", Colours::grey, DocumentWindow::allButtons);
            backColSelWindow->addActionListener(this);
            backColSelWindow->setSize(300, 500);
            backColSelWindow->setVisible(true);
        }
        
        //"Change Waveform Colour" option
        else if(menuItemID == 2)
        {
            //Opens and initilises a new ColourSelectorWindow
            waveColSelWindow = new ColourSelectorWindow("Waveform Colour", Colours::grey, DocumentWindow::allButtons);
            waveColSelWindow->addActionListener(this);
            waveColSelWindow->setSize(300, 500);
            waveColSelWindow->setVisible(true);
        }
    }
}


void MainComponent::buttonClicked(Button* button)
{
    //Open file button
    if(button == &table.queueControls.openFileButton)
    {
        addFile();
    }
    
    //Play/Pause button
    else if(button == &playerGUI.playPauseButton)
    {
        //Checks if the player is currently playing something
        if(player.isPlaying() == false)
        {
            playQueue();
        }
        else if(player.isPlaying() == true)
        {
            pauseAudio();
        }
        
    }
    
    //Stop button
    else if(button == &playerGUI.stopButton)
    {
        stopAudio();
    }
    
    //Next button
    else if(button == &playerGUI.nextButton)
    {
        table.moveIndexToPlayOn();
        setUpPlayer();
    }
    
    //Back button
    else if(button == &playerGUI.lastButton)
    {
        table.moveIndexToPlayBack();
        setUpPlayer();
    }
    
}

void MainComponent::addFile()
{
    //Opens the file chooser to browse for a file and checks it returned something
    if(fileChooser.browseForFileToOpen() == true)
    {
        //Sends new file to the table to be added
        selectedFile = fileChooser.getResult();
        table.addNewItem(&selectedFile);
    }
}

void MainComponent::playQueue()
{
    //Checks if player is currently paused
    if(player.isPaused() == true)
    {
        player.playFromPause();
    }
    else
    {
        //Checks if the table is empty
        if(table.isEmpty() != true)
        {
            //Initilises the table to begin returning files to play
            table.startQueue();
            
            setUpPlayer();
        }
    }
    if(table.isEmpty() != true)
    {
        //Triggers AudioPlayerGUI to change to playing state
        playerGUI.audioPlayed();
        
        //Triggers timers for waveform line and AudioPlayerGUI time label
        Timer:startTimer(100);
    }
}

void MainComponent::pauseAudio()
{
    //checks a file is playing
    if(player.isPlaying() == true)
    {
        player.pause();
        
        //Triggers AudioPlayerGUI to change to paused state
        playerGUI.audioPaused();
    }
}

void MainComponent::stopAudio()
{
    //Tells the table to change indexToPlay to nothing
    table.reset();
    
    //Tells the AudioPlayer to stop playing
    player.stop();
    
    //Stops the waveform line and player GUI time label timer
    Timer::stopTimer();
    
    //Sets AudioPlayerGUI to a stopped state
    playerGUI.audioStopped();
    
    //Clears the waveform
    waveform.clear();
}

void MainComponent::sliderValueChanged(Slider* slider)
{
    if(slider == &playerGUI.gainSlider)
    {
        //Sets the gain of the player based on the gain slider in AudioPlayerGUI
        player.setGain(playerGUI.gainSlider.getValue());
    }
}

void MainComponent::timerCallback()
{
    //Changes the time label in AudioPlayerGUI based on the players position in the audio file
    playerGUI.changeTime(player.getTransportPosition());
    
    if(player.isPlaying() == true)
    {
        //Moves the transport line of the waveform to new position based on the players position in the audio file
        waveform.moveTransportLine((player.getTransportPosition()/player.getTransportLengthInSeconds()) * waveform.getWidth());
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
    
    //Finds this point in the file
    double percentageInTrack = (waveform.getThumbnailLength()/100) * percentageAcrossWaveform;
    
    //Sets the new transport position
    player.setTransportPosition(percentageInTrack);
}

void MainComponent::actionListenerCallback(const String &message)
{
    //If a new row of the table is selected
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
            //Clears the info box if a row isnt selected
            infoBox.clear();
        }
    }
    
    //If the infobox loop button has changed
    else if(message == "Loop button changed")
    {
        //Updates the loop option for the selected item based on the new loop button state
        table.updateSelectedItemLoopToggle(infoBox.getLoopButtonState());
    }
    
    //If the infobox number of loops label has changed
    else if(message == "Number of loops changed")
    {
        //Updates the numloops for the selected item based on the new number of loops selected
        table.updateSelectedItemNumLoops(infoBox.getNewNumLoops());
    }
    
    //If the infobox delete button was pressed
    else if(message == "Delete button pressed")
    {
        table.deleteSelectedItem();
    }
    
    //If the queue has finished playing
    else if(message == "Queue finished")
    {
        stopAudio();
    }
    
    //If the player has finished the current file
    else if(message == "Transport Finished")
    {
        //Prompts the table to select a new file to play
        table.moveIndexToPlayOn();
               
        setUpPlayer();
    }
    
    //If an individual table items play button was played
    else if(message == "Play button on QueueItem pressed")
    {
        //Sends the file to the player but tells it not to send a notification at the end of playback since we only want this file to play, not the whole queue
        player.loadNewFile(table.getFileToPlay(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), false);
        
        //Sets the waveform to the new file to play
        waveform.set(new FileInputSource(*table.getFileToPlay()));
        
        //Triggers the time label and waveform playhead timer
        Timer:startTimer(100);
        
        //Sets playerGUI to playing state
        playerGUI.audioPlayed();
    }
    
    else if(message == "Stop Audio")
    {
        stopAudio();
    }
    
    else if(message == "Mouse Released on Background Colour")
    {
        //Sets the background colour to the colour currently selected in the window
        waveform.setBackgroundColour(backColSelWindow->getColour());
    }
    
    else if(message == "Mouse Released on Waveform Colour")
    {
        //Sets the waveform colour to the colour currently selected in the window
        waveform.setWaveformColour(waveColSelWindow->getColour());
    }
    
    else if(message == "Current Stop Point Changed")
    {
        //Resets the stop point of the player
        player.setStopPoint(table.getCurrentStopPoint());
    }
}

void MainComponent::setUpPlayer()
{
    //Checks there is a file to play
    if(table.getFileToPlay() == nullptr)
    {
        playerGUI.audioStopped();
        stopAudio();
    }
    else
    {
        //Sends the new file to the player to play
        player.loadNewFile(table.getFileToPlay(), table.getCurrentPlayPoint(), table.getCurrentStopPoint(), true);
        
        //Sets the waveform to display the new file
        waveform.set(new FileInputSource(*table.getFileToPlay()));
    }
}
