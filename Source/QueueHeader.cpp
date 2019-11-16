/*
  ==============================================================================

    QueueHeader.cpp
    Created: 16 Nov 2019 7:57:37pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueHeader.h"

//==============================================================================
QueueHeader::QueueHeader()
{
    setSize(500, 30);
}

QueueHeader::~QueueHeader()
{
}

void QueueHeader::paint (Graphics& g)
{
    g.drawRect(0, 0, 500, 30);
    
    g.setColour(Colours::grey);
    g.fillAll();
    
    g.setColour(Colours::black);
    
    g.drawText("ID", 0, 0, 20, 30, Justification::centred);
    g.drawLine(20, 0, 20, 30);
    
    g.drawText("File Name", 20, 0, 135, 30, Justification::centred);
    g.drawLine(155, 0, 155, 30);
    
    g.drawText("File Size", 155, 0, 75, 30, Justification::centred);
    g.drawLine(230, 0, 230, 30);
    
    g.drawText("File Length", 230, 0, 100, 30, Justification::centred);
    g.drawLine(330, 0, 330, 30);
    
    g.drawText("Play Point", 330, 0, 75, 30, Justification::centred);
    g.drawLine(405, 0, 405, 30);
    
    g.drawText("Stop Point", 405, 0, 75, 30, Justification::centred);
    g.drawLine(480, 0, 480, 30);
}

void QueueHeader::resized()
{
    
}
