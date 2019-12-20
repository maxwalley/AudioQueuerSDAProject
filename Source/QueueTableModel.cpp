/*
  ==============================================================================

    QueueTableModel.cpp
    Created: 19 Nov 2019 4:50:50pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueTableModel.h"

//==============================================================================
QueueTableModel::QueueTableModel() : currentIndexPlaying(-1), currentIndexSelected(-1)
{
    addAndMakeVisible(embeddedTable);
    
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
    embeddedTable.setBounds(0, 0, getWidth(), getHeight());
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
    
    /*if (columnId == 2)
    {
        g.setColour(Colours::black);
        g.drawText("Hello", 0, 0, width, height, Justification::centred);
    }*/
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

void QueueTableModel::moveTransportOn()
{
    //Stops transport
    transport.stop();
    
    //Builds on current index
    currentIndexPlaying++;
    
    //Checks to see if we're at the end of the list
    if(currentIndexPlaying != items.size())
    {
        setUpTransport(currentIndexPlaying);
    }
    else
    {
        //Resets current index playing to none
        currentIndexPlaying = -1;
    }
}

void QueueTableModel::startQueue()
{
    //Checks the array isnt empty
    if(items.size() > 0)
    {
        currentIndexPlaying = 0;
        setUpTransport(currentIndexPlaying);
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
                moveTransportOn();
            }
        }
        
        else if(transport.hasStreamFinished() == true)
        {
            moveTransportOn();
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
