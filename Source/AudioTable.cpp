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

void AudioTable::moveTransportOn(bool ignoreLooping)
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
            //Checks that the continuous play button is selected
            if(queueControls.getContinousButtonState() == true)
            {
                setUpTransport(currentIndexPlaying);
            }
            else
            {
                transport.setSource(nullptr);
                sendActionMessage("Break");
            }
            DBG("Activated");
        }
        else
        {
            if(queueControls.getLoopQueueButtonState() == true)
            {
                //Checks that the continuous play button is selected
                if(queueControls.getContinousButtonState() == true)
                {
                    //Restarts the queue
                    startQueue();
                }
                else if(queueControls.getContinousButtonState() == false)
                {
                    transport.setSource(nullptr);
                    //Resets current index playing for the next time
                    currentIndexPlaying = 0;
                    sendActionMessage("Break");
                }
            }
            else
            {
                //Resets current index playing to none
                DBG("Activates");
                currentIndexPlaying = -1;
                sendActionMessage("Queue finished");
            }
        }
    }
}

void AudioTable::moveTransportBack()
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

void AudioTable::startQueue()
{
    //Checks the array isnt empty
    if(items.size() > 0)
    {
        //Checks the audio isn't paused
        if(pausePosition == 0)
        {
            //Checks if continuous play button is ticked
            if(queueControls.getContinousButtonState() == true)
            {
                currentIndexPlaying = 0;
                setUpTransport(currentIndexPlaying);
            }
            else if(queueControls.getContinousButtonState() == false)
            {
                //Checks that its not set to play nothing
                if(currentIndexPlaying == -1)
                {
                    //Resets the playing index to 0 if it is
                    currentIndexPlaying = 0;
                }
                setUpTransport(currentIndexPlaying);
            }
        }
        else
        {
            transport.setPosition(pausePosition);
            transport.start();
        }
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

void AudioTable::stopPointReached()
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
            DBG("Hello");
        }
    }
}

bool AudioTable::itemPlaying() const
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

void AudioTable::setUpTransport(int indexToPlay)
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

void AudioTable::actionListenerCallback(const String &message)
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

File* AudioTable::getCurrentPlayingFile() const
{
    DBG(items[currentIndexPlaying]->getFileName());
    return items[currentIndexPlaying]->getFile();
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

void AudioTable::pauseAudio()
{
    pausePosition = transport.getCurrentPosition();
    transport.stop();
}

void AudioTable::changeQueueControlToggle(int control)
{
    queueControls.changeToggleState(control);
}

void AudioTable::reset()
{
    transport.stop();
    transport.setSource(nullptr);
    currentIndexPlaying = -1;
    pausePosition = 0;
}