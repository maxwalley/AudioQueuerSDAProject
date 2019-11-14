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
QueueDisplayBox::QueueDisplayBox() : mainDisplay(0, 0, 500, 300), item(1)
{
    setSize(500, 300);
    
    addAndMakeVisible(item);
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
    item.setBounds(0, 0, 500, 30);
}
