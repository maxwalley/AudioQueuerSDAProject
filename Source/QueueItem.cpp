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
    setSize(500, 30);
    currentFile = File(*file);
    size = currentFile.getSize();
    
    AudioFormatManager tempManager;
    tempManager.registerBasicFormats();
    reader = tempManager.createReaderFor(currentFile);
    
    lengthInSamples = reader->lengthInSamples;
    sampleRate = reader->sampleRate;
}

QueueItem::~QueueItem()
{
    delete reader;
}

void QueueItem::paint (Graphics& g)
{
    if(itemIndex % 2 == 0 && selected == false)
    {
        g.setColour(Colours::lightblue);
    }
    else if(itemIndex % 2 != 0 && selected == false)
    {
        g.setColour(Colours::orange);
    }
    else
    {
        g.setColour(Colours::darkblue);
    }
    
    g.fillAll();
    
    g.setColour(Colours::black);
    if(lastId == true)
    {
        g.drawLine(0, 30, 500, 30);
    }
   
    g.drawText(String(itemIndex), 0, 0, 20, 30, Justification::centred);
    g.drawLine(20, 0, 20, 30);
    
    g.drawText(currentFile.getFileName(), 20, 0, 135, 30, Justification::centred);
    g.drawLine(155, 0, 155, 30);
    
    g.drawText(String(size), 155, 0, 75, 30, Justification::centred);
    g.drawLine(230, 0, 230, 30);
    
    workOutTime();
    g.drawText(lengthInTime, 230, 0, 100, 30, Justification::centred);
    g.drawLine(330, 0, 330, 30);
    
    
}

void QueueItem::resized()
{
    
}

String QueueItem::getFileName()
{
    return currentFile.getFileName();
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
