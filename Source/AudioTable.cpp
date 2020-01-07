/*
  ==============================================================================

    QueueTableModel.cpp
    Created: 19 Nov 2019 4:50:50pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioTable.h"
#include "QueueControls.h"

//==============================================================================
AudioTable::AudioTable() : currentIndexPlaying(-1), currentIndexSelected(-1), loopCounter(0)
{
    addAndMakeVisible(embeddedTable);
    
    addAndMakeVisible(queueControls);
    
    embeddedTable.setHeader(&header);
    embeddedTable.setModel(this);
    
    items.clear();
}

AudioTable::~AudioTable()
{
    for(int i = 0; i < items.size(); i++)
    {
        delete items[i];
    }
}

void AudioTable::paint(Graphics& g)
{
    header.setColour(TableHeaderComponent::ColourIds::textColourId, Colours::black);
    
    embeddedTable.setColour(ListBox::ColourIds::backgroundColourId, Colours::lightgrey);
}

void AudioTable::resized()
{
    queueControls.setBounds(0, 0, 150, 300);
    embeddedTable.setBounds(200, 0, 550, getHeight());
}

int AudioTable::getNumRows()
{
    return items.size();
}

void AudioTable::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowIsSelected == true)
    {
        g.setColour(Colours::grey);
    }
    else
    {
        g.setColour(Colours::white);
    }
    
    g.fillAll();
}

void AudioTable::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    String stringToDraw;
    
    if(columnId == 1)
    {
        stringToDraw = String(items[rowNumber]->getItemIndex() + 1);
    }
    
    else if(columnId == 2)
    {
        stringToDraw = items[rowNumber]->getFileName();
    }
    
    else if(columnId == 3)
    {
        stringToDraw = String(items[rowNumber]->getFileSize());
    }
    
    else if(columnId == 4)
    {
        stringToDraw = items[rowNumber]->getLengthInTime();
    }
    
    g.setColour(Colours::black);
    g.drawText(stringToDraw, 0, 0, width, height, Justification::centred);
}

Component* AudioTable::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if(columnId == 5)
    {
        return items[rowNumber]->getPlayTimeLabel();
    }
    
    else if(columnId == 6)
    {
        return items[rowNumber]->getStopTimeLabel();
    }
    
    else if(columnId == 7)
    {
        return items[rowNumber]->getPlayButton();
    }
    
    else
    {
        return nullptr;
    }
}

void AudioTable::addNewItem(File* file)
{
    int nextIndex = items.size();
    
    QueueItem* newItem = new QueueItem(nextIndex, file);
    
    items.add(newItem);
    
    //Adds this as an action listener for the new item
    items[nextIndex]->addActionListener(this);

    embeddedTable.updateContent();
}

void AudioTable::deleteSelectedItem()
{
    items.remove(currentIndexSelected);
    
    embeddedTable.updateContent();
    
    //Resets the selected index since nothing will be selected
    currentIndexSelected = -1;
}

void AudioTable::selectedRowsChanged(int lastRowSelected)
{
    //Sets current index selected to the selected row
    currentIndexSelected = lastRowSelected;
    
    //Sends message to main component to trigger infoBox to change
    sendActionMessage("Selected Item Changed");
}

int AudioTable::getSelectedRow()
{
    return embeddedTable.getSelectedRow();
}

void AudioTable::moveTransportOn()
{
    //if current item is set to loop and the specified amount of loops have not been hit
    if(items[currentIndexPlaying]->getLoop() == true && items[currentIndexPlaying]->getNumLoops() > loopCounter)
    {
        loopCounter++;
    }
    else
    {
        loopCounter = 0;
        
        //If queue is set to shuffle
        if(queueControls.getShuffleQueueButtonState() == true)
        {
            //Gets a random value in the range of how many items there are
            currentIndexPlaying = Random::getSystemRandom().nextInt(items.size());
        }
        
        //If we're not at the end of the queue
        else if(currentIndexPlaying < items.size() - 1)
        {
            currentIndexPlaying++;
        }
        
        else
        {
            //If queue is set to loop
            if(queueControls.getLoopQueueButtonState() == true)
            {
                //Reset index to play
                currentIndexPlaying = 0;
            }
            else
            {
                currentIndexPlaying = -1;
            }
        }
    }
    
    //If the play continuosly button is not active
    if(queueControls.getContinousButtonState() == false)
    {
        //Stores the next index
        nextIndexToPlay = currentIndexPlaying;
        
        //Sets current index to not playing
        currentIndexPlaying = -1;
    }
    else
    {
        nextIndexToPlay = -1;
    }
    
    DBG("Current Index = " << currentIndexPlaying);
}


void AudioTable::moveTransportBack()
{
    //Checks to see something is playing
    if(currentIndexPlaying != -1)
    {
        //Checks to see if current playing item is not the first on the list
        if(currentIndexPlaying != 0)
        {
            currentIndexPlaying--;
        }
    }
}

void AudioTable::startQueue()
{
    //Checks the array isnt empty
    if(items.size() > 0)
    {
        //Resets the current index
        currentIndexPlaying = 0;
            
        if(queueControls.getContinousButtonState() == false)
        {
            //Checks that its not set to play nothing
            if(nextIndexToPlay != -1)
            {
                //Resumes playing from last stop
                currentIndexPlaying = nextIndexToPlay;
            }
        }
    }
    else
    {
        currentIndexPlaying = -1;
    }
}

int AudioTable::getCurrentPlayPoint() const
{
    //Checks a file is playing
    if(currentIndexPlaying != -1)
    {
        return items[currentIndexPlaying]->getPlayPoint();
    }
}

int AudioTable::getCurrentStopPoint() const
{
    //Checks a file is playing
    if(currentIndexPlaying != -1)
    {
        return items[currentIndexPlaying]->getStopPoint();
    }
}

void AudioTable::actionListenerCallback(const String &message)
{
    //Checks message is from a play button
    if(message.startsWith("Play button pressed on index:") == true)
    {
        //Takes last character of the message and finds out what number it is. Then uses this number as the index to play
        String indexNumString = message.getLastCharacters(1);
        currentIndexPlaying = indexNumString.getIntValue();
        sendActionMessage("Play button on QueueItem pressed");
    }
}

File* AudioTable::getCurrentPlayingFile() const
{
    if(currentIndexPlaying != -1)
    {
        return items[currentIndexPlaying]->getFile();
    }
    else
    {
        return nullptr;
    }
}

ItemInfo AudioTable::getCurrentPlayingDataStruct() const
{
    return items[currentIndexPlaying]->getItemData();
}

ItemInfo AudioTable::getCurrentSelectedDataStruct() const
{
    return items[currentIndexSelected]->getItemData();
}

void AudioTable::setTransportPosition(double newPosition)
{
    transport.setPosition(newPosition);
}

void AudioTable::updateSelectedItemLoopToggle(bool newLoopToggle)
{
    items[currentIndexSelected]->setLoop(newLoopToggle);
}

void AudioTable::updateSelectedItemNumLoops(int newNumLoops)
{
    items[currentIndexSelected]->setNumLoops(newNumLoops);
}

void AudioTable::changeQueueControlToggle(int control)
{
    queueControls.changeToggleState(control);
}

void AudioTable::reset()
{
    currentIndexPlaying = -1;
}
