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
QueueItem::QueueItem(int index/*, File file*/)
{
    itemIndex = index;
    setSize(500, 30);
    
}

QueueItem::~QueueItem()
{
    
}

void QueueItem::paint (Graphics& g)
{
    if(itemIndex % 2 == 0)
    {
        g.setColour(Colours::lightblue);
    }
    else
    {
        g.setColour(Colours::orange);
    }
    
    g.fillAll();
    
    g.setColour(Colours::black);
    if(lastId == true)
    {
        g.drawLine(0, 30, 500, 30);
    }
   
    g.drawText(String(itemIndex), 0, 0, 20, 30, Justification::centred);
    g.drawLine(20, 0, 20, 30);
}

void QueueItem::resized()
{
    
}
