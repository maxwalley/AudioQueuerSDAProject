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
QueueDisplayBox::QueueDisplayBox() : mainDisplay(0, 0, 500, 300), selectedItem(0)
{
    setSize(500, 300);
    
    addAndMakeVisible(header);
    
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
    header.setBounds(0, 0, 500, 30);
}

void QueueDisplayBox::addNewItem(File* file)
{
    int currentID = items.size();
    
    QueueItem newItem(currentID + 1, file);
    
    items.add(&newItem);
    
    items[currentID]->setLast(true);
    if(currentID != 0)
    {
        items[currentID-1]->setLast(false);
    }

    items[selectedItem]->setSelected(false);
    items[currentID]->setSelected(true);
    
    DBG(items[currentID]->getFileName());
    
    addAndMakeVisible(items[currentID]);
    items[currentID]->setBounds(0, 30, 500, 30);
    
    selectedItem = currentID;
}

void QueueDisplayBox::mouseDown(const MouseEvent &event)
{
    items[selectedItem]->setSelected(false);
    
    selectedItem = floor(event.getMouseDownScreenY()/30);
    
    items[selectedItem]->setSelected(true);
}
