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
    itemData.itemIndex = idNum;
    itemData.currentFile = file;
    itemData.size = itemData.currentFile->getSize();
    
    //currentFile = File(*file);
    //size = currentFile.getSize();
    
    AudioFormatManager tempManager;
    tempManager.registerBasicFormats();
    reader = tempManager.createReaderFor(*itemData.currentFile);
    
    if(reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> tempAudioFormatReaderSource (new AudioFormatReaderSource (reader, true));
    
        audioFormatReaderSource.reset(tempAudioFormatReaderSource.release());
    }
    
    itemData.lengthInSamples = reader->lengthInSamples;
    itemData.sampleRate = reader->sampleRate;
    
    playButton.addListener(this);
    
    playTimeLabel.setEditable(false, true, false);
    playTimeLabel.addListener(this);
    stopTimeLabel.setEditable(false, true, false);
    stopTimeLabel.addListener(this);
    
    playLabelTime.preColonNum = 0;
    playLabelTime.postColonNum = 0;
    
    stopLabelTime.preColonNum = 0;
    stopLabelTime.postColonNum = 0;
}

QueueItem::~QueueItem()
{
    delete reader;
}

void QueueItem::paint (Graphics& g)
{
    
}

void QueueItem::resized()
{
    
}

File* QueueItem::getFile()
{
    return itemData.currentFile;
}

int QueueItem::getItemIndex() const
{
    return itemData.itemIndex;
}

void QueueItem::setItemIndex(int index)
{
    itemData.itemIndex = index;
}

String QueueItem::getFileName()
{
    return itemData.currentFile->getFileName();
}

int64_t QueueItem::getFileSize()
{
    return itemData.size;
}

void QueueItem::workOutLengthInSecs()
{
    itemData.lengthInSecs = floor(itemData.lengthInSamples/itemData.sampleRate);
}

void QueueItem::workOutTime()
{
    workOutLengthInSecs();
    
    int numMins = floor(itemData.lengthInSecs/60);
    int numSecs = (fmod(itemData.lengthInSecs, 60));
    
    std::string numMinsString = std::to_string(numMins);
    std::string numSecsString = std::to_string(numSecs);
    
    itemData.lengthInTime = numMinsString + ":" + numSecsString;
}

String QueueItem::getLengthInTime()
{
    workOutTime();
    return itemData.lengthInTime;
}

Label* QueueItem::getPlayTimeLabel()
{
    return &playTimeLabel;
}

Label* QueueItem::getStopTimeLabel()
{
    return &stopTimeLabel;
}

PlayButton* QueueItem::getPlayButton()
{
    return &playButton;
}

double QueueItem::getSampleRate()
{
    return itemData.sampleRate;
}

int QueueItem::getNumChannels()
{
    return itemData.numChannels;
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
            labelThatHasChanged->setText("", dontSendNotification);
        }
        
        //Looks for ':'
        else if(currentChar.compare(":") == 0)
        {
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
    
    if(labelThatHasChanged == &playTimeLabel)
    {
        playLabelTime.preColonNum = preColonStr.getIntValue();
        playLabelTime.postColonNum = postColonStr.getIntValue();
    }
    else if (labelThatHasChanged == &stopTimeLabel)
    {
        stopLabelTime.preColonNum = preColonStr.getIntValue();
        stopLabelTime.postColonNum = postColonStr.getIntValue();
    }
}

void QueueItem::buttonClicked(Button* button)
{
    //Checks its the play button thats been pressed
    if(button == &playButton)
    {
        //Puts the item index into a string
        String indexNumString(itemData.itemIndex);
        
        sendActionMessage("Play button pressed on index:" + indexNumString);
    }
}

int QueueItem::getPlayPoint()
{
    return (playLabelTime.preColonNum * 60) + playLabelTime.postColonNum;
}

int QueueItem::getStopPoint()
{
    return (stopLabelTime.preColonNum * 60) + stopLabelTime.postColonNum;
}

ItemInfo QueueItem::getItemData() const
{
    return itemData;
}
