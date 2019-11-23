/*
  ==============================================================================

    QueueTable.cpp
    Created: 19 Nov 2019 4:50:39pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueTable.h"

//==============================================================================
QueueTable::QueueTable()
{
    setSize(500, 300);
    
    setHeader(&header);
}

QueueTable::~QueueTable()
{
}

void QueueTable::paint (Graphics& g)
{
    
}

void QueueTable::resized()
{
    
}

void QueueTable::addItem(File* file)
{
    updateContent();
}
