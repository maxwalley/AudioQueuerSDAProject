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
QueueItem::QueueItem(int idNum, File* file) : itemIndex(idNum)
{
    currentFile = File(*file);
    size = currentFile.getSize();
    
    AudioFormatManager tempManager;
    tempManager.registerBasicFormats();
    reader = tempManager.createReaderFor(currentFile);
    
    if(reader != nullptr)
    {
        std::unique_ptr<AudioFormatReaderSource> tempAudioFormatReaderSource (new AudioFormatReaderSource (reader, true));
    
        //audioTransportSource.setSource(tempAudioFormatReaderSource.get(), 0, nullptr, reader->sampleRate, reader->numChannels);
    
        audioFormatReaderSource.reset(tempAudioFormatReaderSource.release());
    }
    
    lengthInSamples = reader->lengthInSamples;
    sampleRate = reader->sampleRate;
    
    playTimeLabel.setEditable(false, true, false);
    playTimeLabel.addListener(this);
    stopTimeLabel.setEditable(false, true, false);
    stopTimeLabel.addListener(this);
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
    return &currentFile;
}

int QueueItem::getItemIndex() const
{
    return itemIndex;
}

void QueueItem::setItemIndex(int index)
{
    itemIndex = index;
}

String QueueItem::getFileName()
{
    return currentFile.getFileName();
}

int64_t QueueItem::getFileSize()
{
    return size;
}

void QueueItem::workOutLengthInSecs()
{
    lengthInSecs = floor(lengthInSamples/sampleRate);
}

void QueueItem::workOutTime()
{
    workOutLengthInSecs();
    
    int numMins = floor(lengthInSecs/60);
    int numSecs = (fmod(lengthInSecs, 60)) * 60;
    
    std::string numMinsString = std::to_string(numMins);
    std::string numSecsString = std::to_string(numSecs);
    
    lengthInTime = numMinsString + ":" + numSecsString;
}

String QueueItem::getLengthInTime()
{
    workOutTime();
    return lengthInTime;
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

void QueueItem::setLast(bool last)
{
    lastId = last;
    if(last == false)
    {
        repaint();
    }
}

void QueueItem::setSelected(bool isSelected)
{
    selected = isSelected;
    repaint();
}

double QueueItem::getReaderSampleRate()
{
    return reader->sampleRate;
}

int QueueItem::getReaderNumChannels()
{
    return reader->numChannels;
}

void QueueItem::labelTextChanged(Label* labelThatHasChanged)
{
    String newText = labelThatHasChanged->getText();
    int textLength = newText.length();
    
    for(int i = 0; i < textLength; i++)
    {
        String currentChar = String::charToString(newText[i]);
        
        if(currentChar.compare("0") != 0 && currentChar.compare("1") != 0 && currentChar.compare("2") != 0 && currentChar.compare("3") != 0 && currentChar.compare("4") != 0 && currentChar.compare("5") != 0 && currentChar.compare("6") != 0 && currentChar.compare("7") != 0 && currentChar.compare("8") != 0 && currentChar.compare("9") != 0 && currentChar.compare(":") != 0)
        {
            labelThatHasChanged->setText("", dontSendNotification);
        }
    }
}
