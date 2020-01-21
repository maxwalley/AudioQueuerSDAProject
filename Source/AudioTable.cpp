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
AudioTable::AudioTable() : indexToPlay(-1), currentIndexSelected(-1), loopCounter(0)
{
    addAndMakeVisible(embeddedTable);
    
    addAndMakeVisible(queueControls);
    
    embeddedTable.setHeader(new QueueTableHeader());
    embeddedTable.setModel(this);
}

AudioTable::~AudioTable()
{
    
}

void AudioTable::paint(Graphics& g)
{
    embeddedTable.getHeader().setColour(TableHeaderComponent::ColourIds::textColourId, Colours::black);
    
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
        //return items[rowNumber]->getPlayTimeLabel();
        return nullptr;

    }
    
    else if(columnId == 6)
    {
        //return items[rowNumber]->getStopTimeLabel();
        return nullptr;
    }
    
    else if(columnId == 7)
    {
        //return items[rowNumber]->getPlayButton();
        
        items[rowNumber]->setPlayButton(new PlayButton());
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
    
    items.add(new QueueItem(nextIndex, file));
    
    //Adds this as an action listener for the new item
    items[nextIndex]->addActionListener(this);
    
    embeddedTable.updateContent();
}

void AudioTable::deleteSelectedItem()
{
    //If the deleted item is the one playing or about to play
    if(currentIndexSelected == indexToPlay)
    {
        sendActionMessage("Stop Audio");
        indexToPlay = -1;
    }
    
    items.remove(currentIndexSelected, true);
    
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

void AudioTable::moveIndexToPlayOn()
{
    //if current item is set to loop and the specified amount of loops have not been hit
    if(items[indexToPlay]->getLoop() == true && items[indexToPlay]->getNumLoops() > loopCounter)
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
            indexToPlay = Random::getSystemRandom().nextInt(items.size());
        }
        
        //If we're not at the end of the queue
        else if(indexToPlay < items.size() - 1)
        {
            indexToPlay++;
        }
        
        else
        {
            //If queue is set to loop
            if(queueControls.getLoopQueueButtonState() == true)
            {
                //Reset index to play
                indexToPlay = 0;
            }
            else
            {
                indexToPlay = -1;
            }
        }
    }
    
    //If the play continuously button is not active
    if(queueControls.getContinuousButtonState() == false)
    {
        //Stores the next index
        nextIndexToPlay = indexToPlay;
        
        //Sets current index to not playing
        indexToPlay = -1;
    }
    else
    {
        nextIndexToPlay = -1;
    }
    
    DBG("Current Index = " << indexToPlay);
}


void AudioTable::moveIndexToPlayBack()
{
    //Checks to see something is playing
    if(indexToPlay != -1)
    {
        //Checks to see if current playing item is not the first on the list
        if(indexToPlay != 0)
        {
            indexToPlay--;
        }
        else
        {
            indexToPlay = -1;
        }
    }
}

void AudioTable::startQueue()
{
    //Checks the array isnt empty
    if(items.size() > 0)
    {
        //Resets the current index
        indexToPlay = 0;
            
        if(queueControls.getContinuousButtonState() == false)
        {
            //Checks that its not set to play nothing
            if(nextIndexToPlay != -1)
            {
                //Resumes playing from last stop
                indexToPlay = nextIndexToPlay;
            }
        }
    }
    else
    {
        indexToPlay = -1;
    }
}

int AudioTable::getCurrentPlayPoint() const
{
    //Checks a file is playing
    if(indexToPlay != -1)
    {
        return items[indexToPlay]->getPlayPoint();
    }
}

int AudioTable::getCurrentStopPoint() const
{
    //Checks a file is playing
    if(indexToPlay != -1)
    {
        return items[indexToPlay]->getStopPoint();
    }
}

void AudioTable::actionListenerCallback(const String &message)
{
    //Checks message is from a play button
    if(message.startsWith("Play button pressed on index:") == true)
    {
        //Takes last character of the message and finds out what number it is. Then uses this number as the index to play
        String indexNumString = message.getLastCharacters(1);
        indexToPlay = indexNumString.getIntValue();
        sendActionMessage("Play button on QueueItem pressed");
    }
}

File* AudioTable::getFileToPlay() const
{
    if(indexToPlay != -1)
    {
        return items[indexToPlay]->getFile();
    }
    else
    {
        return nullptr;
    }
}

ItemInfo AudioTable::getCurrentPlayingDataStruct() const
{
    return items[indexToPlay]->getItemData();
}

ItemInfo AudioTable::getCurrentSelectedDataStruct() const
{
    return items[currentIndexSelected]->getItemData();
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
    indexToPlay = -1;
}

bool AudioTable::isEmpty()
{
    if(items.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool AudioTable::isRowSelected()
{
    if(embeddedTable.getNumSelectedRows() == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
