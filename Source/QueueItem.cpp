/*
  ==============================================================================

    QueueItem.cpp
    Created: 14 Nov 2019 12:47:10pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueItem.h"

//==============================================================================
QueueItem::QueueItem(int idNum, File* file)
{
    formatManager.registerBasicFormats();
    reader = formatManager.createReaderFor(*file);
    
    
    //Fills all the variables of the ItemInfo for this instance with data from the file
    itemData.itemIndex = idNum;
    itemData.file = *file;
    itemData.fileName = itemData.file.getFileName();
    itemData.size = itemData.file.getSize();
    
    itemData.lengthInSamples = reader->lengthInSamples;
    itemData.sampleRate = reader->sampleRate;
    itemData.numChannels = reader->numChannels;
    
    itemData.loop = false;
    itemData.numLoops = 0;
    
    
    playTimeLabel = new Label();
    playTimeLabel->setColour(Label::ColourIds::textColourId, Colours::black);
    playTimeLabel->setColour(Label::ColourIds::textWhenEditingColourId, Colours::black);
    playTimeLabel->setEditable(false, true, false);
    playTimeLabel->addListener(this);
    
    stopTimeLabel = new Label();
    stopTimeLabel->setColour(Label::ColourIds::textColourId, Colours::black);
    stopTimeLabel->setColour(Label::ColourIds::textWhenEditingColourId, Colours::black);
    stopTimeLabel->setEditable(false, true, false);
    stopTimeLabel->addListener(this);
    
    playLabelTime.preColonNum = 0;
    playLabelTime.postColonNum = 0;
    
    stopLabelTime.preColonNum = 0;
    stopLabelTime.postColonNum = 0;
    
    playButton = new PlayButton();
    playButton->addListener(this);
}

QueueItem::~QueueItem()
{
    delete reader;
}

void QueueItem::setFile(File* file)
{
    itemData.file = *file;
}

File* QueueItem::getFile()
{
    return &itemData.file;
}

void QueueItem::setItemIndex(int index)
{
    itemData.itemIndex = index;
}

int QueueItem::getItemIndex() const
{
    return itemData.itemIndex;
}

String QueueItem::getFileName() const
{
    return itemData.fileName;
}

int64_t QueueItem::getFileSize() const
{
    return itemData.size;
}

void QueueItem::workOutLengthInSecs()
{
    //Time in seconds = number of samples / sample rate
    itemData.lengthInSecs = floor(itemData.lengthInSamples/itemData.sampleRate);
}

void QueueItem::workOutTime()
{
    workOutLengthInSecs();
    
    //Works out the number of minutes and seconds in that many seconds
    int numMins = floor(itemData.lengthInSecs/60);
    int numSecs = (fmod(itemData.lengthInSecs, 60));
    
    //Converts these both to strings
    std::string numMinsString = std::to_string(numMins);
    std::string numSecsString = std::to_string(numSecs);
    
    //Adds the strings together
    itemData.lengthInTime = numMinsString + ":" + numSecsString;
}

String QueueItem::getLengthInTime()
{
    workOutTime();
    return itemData.lengthInTime;
}

Label* QueueItem::getPlayTimeLabel()
{
    return playTimeLabel;
}

Label* QueueItem::getStopTimeLabel()
{
    return stopTimeLabel;
}

PlayButton* QueueItem::getPlayButton()
{
    return playButton;
}

void QueueItem::labelTextChanged(Label* labelThatHasChanged)
{
    String newText = labelThatHasChanged->getText();
    int textLength = newText.length();
    int colonIndex = 0;
    String preColonStr = "";
    String postColonStr = "";
    
    //Iterates through new text
    for(int i = 0; i < textLength; i++)
    {
        String currentChar = String::charToString(newText[i]);
        
        //Checks for anything other than a digit or ':'
        if(currentChar.compare("0") != 0 && currentChar.compare("1") != 0 && currentChar.compare("2") != 0 && currentChar.compare("3") != 0 && currentChar.compare("4") != 0 && currentChar.compare("5") != 0 && currentChar.compare("6") != 0 && currentChar.compare("7") != 0 && currentChar.compare("8") != 0 && currentChar.compare("9") != 0 && currentChar.compare(":") != 0)
        {
            //Resets the label if it finds anything other than a digit or ':'
            labelThatHasChanged->setText("", dontSendNotification);
        }
        
        //Looks for ':'
        else if(currentChar.compare(":") == 0)
        {
            //Sets the colon index to where it finds this
            colonIndex = i;
        }
    }

    //Puts the mins in this string
    for(int i = 0; i < colonIndex; i++)
    {
        preColonStr += newText[i];
    }
    
    //Puts the secs in this string
    for(int i = colonIndex + 1; i < textLength; i++)
    {
        postColonStr += newText[i];
    }
    
    //Adds these to their specific labelTimes struct
    if(labelThatHasChanged == playTimeLabel)
    {
        //Converts from string to int
        playLabelTime.preColonNum = preColonStr.getIntValue();
        playLabelTime.postColonNum = postColonStr.getIntValue();
    }
    else if (labelThatHasChanged == stopTimeLabel)
    {
        //Converts from string to int
        stopLabelTime.preColonNum = preColonStr.getIntValue();
        stopLabelTime.postColonNum = postColonStr.getIntValue();
        
        //Sends this message which holds the item index at the end
        sendActionMessage("Stop Point Changed on index:" + String(itemData.itemIndex));
    }
}

void QueueItem::buttonClicked(Button* button)
{
    //Converts the item index into a string
    String indexNumString(itemData.itemIndex);
        
    //Sends this message which holds the item index at the end
    sendActionMessage("Play button pressed on index:" + indexNumString);
}

int QueueItem::getPlayPoint() const
{
    return (playLabelTime.preColonNum * 60) + playLabelTime.postColonNum;
}

int QueueItem::getStopPoint() const
{
    return (stopLabelTime.preColonNum * 60) + stopLabelTime.postColonNum;
}

ItemInfo QueueItem::getItemData() const
{
    return itemData;
}

void QueueItem::setLoop(bool loop)
{
    itemData.loop = loop;
}

bool QueueItem::getLoop() const
{
    return itemData.loop;
}

void QueueItem::setNumLoops(int numLoops)
{
    itemData.numLoops = numLoops;
}

int QueueItem::getNumLoops() const
{
    return itemData.numLoops;
}
