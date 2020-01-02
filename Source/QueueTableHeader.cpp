/*
  ==============================================================================

    QueueTableHeader.cpp
    Created: 19 Nov 2019 5:01:29pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueTableHeader.h"

//==============================================================================
QueueTableHeader::QueueTableHeader()
{
    addColumn("ID", 1, 20, 5, -1, 63, 0);
    addColumn("File Name", 2, 135, 25, -1, 63, 1);
    addColumn("File Size", 3, 75, 12, -1, 63, 2);
    addColumn("File Length", 4, 100, 25, -1, 63, 3);
    addColumn("Play Point", 5, 75, 12, -1, 63, 4);
    addColumn("Stop Point", 6, 75, 12, -1, 63, 5);
    addColumn("Play", 7, 70, 5, -1, 63, 6);
}

QueueTableHeader::~QueueTableHeader()
{
    
}
