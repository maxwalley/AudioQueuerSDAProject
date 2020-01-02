/*
  ==============================================================================

    QueueTableModel.cpp
    Created: 19 Nov 2019 4:50:50pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueTableModel.h"
#include "QueueControls.h"

//==============================================================================
QueueTableModel::QueueTableModel() : currentIndexPlaying(-1), currentIndexSelected(-1), loopCounter(0)
{
    addAndMakeVisible(embeddedTable);
    
    addAndMakeVisible(queueControls);
    
    embeddedTable.setHeader(&header);
    embeddedTable.setModel(this);
    
    items.clear();
}

QueueTableModel::~QueueTableModel()
{
    for(int i = 0; i < items.size(); i++)
    {
        delete items[i];
    }
}

void QueueTableModel::resized()
{
    queueControls.setBounds(0, 0, 150, 300);
    embeddedTable.setBounds(200, 0, 550, getHeight());
}

int QueueTableModel::getNumRows()
{
    return items.size();
}

void QueueTableModel::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowIsSelected == true)
    {
        g.setColour(Colours::green);
    }
    else if(rowNumber % 2 == 0)
    {
        g.setColour(Colours::lightblue);
    }
    else if(rowNumber % 2 != 0)
    {
        g.setColour(Colours::orange);
    }
    
    g.fillAll();
}

void QueueTableModel::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
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

Component* QueueTableModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
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

void QueueTableModel::addNewItem(File* file)
{
    int nextIndex = items.size();
    
    QueueItem* newItem = new QueueItem(nextIndex, file);
    
    items.add(newItem);
    
    //Adds this as an action listener for the new item
    items[nextIndex]->addActionListener(this);

    embeddedTable.updateContent();
}

void QueueTableModel::deleteSelectedItem()
{
    items.remove(currentIndexSelected);
    
    embeddedTable.updateContent();
    
    //Resets the selected index since nothing will be selected
    currentIndexSelected = -1;
}

void QueueTableModel::selectedRowsChanged(int lastRowSelected)
{
    //Sets current index selected to the selected row
    currentIndexSelected = lastRowSelected;
    
    //Sends message to main component to trigger infoBox to change
    sendActionMessage("Selected Item Changed");
}

int QueueTableModel::getSelectedRow()
{
    return embeddedTable.getSelectedRow();
}

void QueueTableModel::moveTransportOn(bool ignoreLooping)
{
    //Stops transport
    transport.stop();
    
    //Checks to see something is playing
    if(currentIndexPlaying != -1)
    {
        //Checks to see if looping mechanism should be skipped
        if(ignoreLooping == false)
        {
            //Checks to see if the item is set to loop
            if(items[currentIndexPlaying]->getLoop() == true)
            {
                //Checks to see if the specified number of loops have been completed
                if(items[currentIndexPlaying]->getNumLoops() > loopCounter)
                {
                    loopCounter++;
                }
                else
                {
                    loopCounter = 0;
                    currentIndexPlaying++;
                }
            }
            else
            {
                //Moves index onto next
                currentIndexPlaying++;
            }
        }
        else
        {
            currentIndexPlaying++;
        }
    
        //Checks that a loop is not currently being played
        if(loopCounter == 0)
        {
            //If shuffle is on
            if(queueControls.getShuffleQueueButtonState() == true)
            {
                //Gets a random value in the range of how many items there are
                currentIndexPlaying = Random::getSystemRandom().nextInt(items.size());
            }
        }
        
        //Checks to see if we're at the end of the list or the shuffle button is enabled
        if(currentIndexPlaying != items.size() || queueControls.getShuffleQueueButtonState() == true)
        {
            setUpTransport(currentIndexPlaying);
        }
        else
        {
            if(queueControls.getLoopQueueButtonState() == true)
            {
                //Restarts the queue
                startQueue();
            }
            else
            {
                //Resets current index playing to none
                currentIndexPlaying = -1;
                sendActionMessage("Queue finished");
            }
        }
    }
}

void QueueTableModel::moveTransportBack()
{
    transport.stop();
    
    //Checks to see something is playing
    if(currentIndexPlaying != -1)
    {
        //Checks to see if current playing item is not the first on the list
        if(currentIndexPlaying != 0)
        {
            currentIndexPlaying--;
            
            setUpTransport(currentIndexPlaying);
        }
    }
}

void QueueTableModel::startQueue()
{
    //Checks the array isnt empty
    if(items.size() > 0)
    {
        //Checks the audio isn't paused
        if(pausePosition == 0)
        {
            currentIndexPlaying = 0;
            setUpTransport(currentIndexPlaying);
        }
        else
        {
            transport.setPosition(pausePosition);
            transport.start();
        }
    }
}

int QueueTableModel::getCurrentStopPoint() const
{
    //Checks a file is playing
    if(currentIndexPlaying != -1)
    {
        return items[currentIndexPlaying]->getStopPoint();
    }
}

void QueueTableModel::stopPointReached()
{
    //Checks a file is playing
    if(currentIndexPlaying != -1)
    {
        //Checks if the user has specified a stop point
        if (items[currentIndexPlaying]->getStopPoint() != 0)
        {
            //Checks if current position is after the stop point
            if(transport.getCurrentPosition() >= items[currentIndexPlaying]->getStopPoint())
            {
                moveTransportOn(false);
            }
        }
        
        //Checks if the file has finished
        else if(transport.hasStreamFinished() == true)
        {
            moveTransportOn(false);
        }
    }
}

bool QueueTableModel::itemPlaying() const
{
    if(currentIndexPlaying != -1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void QueueTableModel::setUpTransport(int indexToPlay)
{
    if(transport.isPlaying() == true)
    {
        transport.stop();
    }
    
    transport.setSource(items[indexToPlay]->audioFormatReaderSource.get(), 0, nullptr, items[indexToPlay]->getSampleRate(), items[indexToPlay]->getNumChannels());
    transport.setPosition(items[indexToPlay]->getPlayPoint());
    
    //Sends message to main component so thumbnail can be changed
    sendActionMessage("Playing Item Changed");
    
    //Resets pause position
    pausePosition = 0;
    
    DBG("Transport starting at index:" << indexToPlay);
    
    transport.start();
}

void QueueTableModel::actionListenerCallback(const String &message)
{
    //Checks message is from a play button
    if(message.startsWith("Play button pressed on index:") == true)
    {
        //Takes last character of the message and finds out what number it is. Then uses this number as the index to play
        String indexNumString = message.getLastCharacters(1);
        currentIndexPlaying = indexNumString.getIntValue();
        setUpTransport(currentIndexPlaying);
    }
}

File* QueueTableModel::getCurrentPlayingFile() const
{
    DBG(items[currentIndexPlaying]->getFileName());
    return items[currentIndexPlaying]->getFile();
}

ItemInfo QueueTableModel::getCurrentPlayingDataStruct() const
{
    return items[currentIndexPlaying]->getItemData();
}

ItemInfo QueueTableModel::getCurrentSelectedDataStruct() const
{
    return items[currentIndexSelected]->getItemData();
}

void QueueTableModel::setTransportPosition(double newPosition)
{
    transport.setPosition(newPosition);
}

void QueueTableModel::updateSelectedItemLoopToggle(bool newLoopToggle)
{
    items[currentIndexSelected]->setLoop(newLoopToggle);
}

void QueueTableModel::updateSelectedItemNumLoops(int newNumLoops)
{
    items[currentIndexSelected]->setNumLoops(newNumLoops);
}

void QueueTableModel::pauseAudio()
{
    pausePosition = transport.getCurrentPosition();
    transport.stop();
}
