/*
  ==============================================================================

    QueueDisplayBox.cpp
    Created: 12 Nov 2019 9:58:58pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueDisplayBox.h"

//==============================================================================
QueueDisplayBox::QueueDisplayBox() : mainDisplay(0, 0, 500, 300)
{
    setSize(500, 300);
    
}

QueueDisplayBox::~QueueDisplayBox()
{
}

void QueueDisplayBox::paint (Graphics& g)
{
    g.drawRect(mainDisplay);
}

void QueueDisplayBox::resized()
{
    
}

void QueueDisplayBox::addNewItem(File* file)
{
    int nextID = items.size() + 1;
    
    QueueItem newItem(nextID, file);
    
    items.add(&newItem);
    
    DBG(items[nextID-1]->getFileName());
    
    addAndMakeVisible(items[nextID-1]);
    items[nextID-1]->setBounds(0, 0, 500, 30);
    
    
}
