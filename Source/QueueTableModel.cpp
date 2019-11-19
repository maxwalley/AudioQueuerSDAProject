/*
  ==============================================================================

    QueueTableModel.cpp
    Created: 19 Nov 2019 4:50:50pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueTableModel.h"

//==============================================================================
QueueTableModel::QueueTableModel()
{
    items.clear();
}

QueueTableModel::~QueueTableModel()
{
    
}

int QueueTableModel::getNumRows()
{
    return items.size();
}

void QueueTableModel::paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected)
{
    if(rowIsSelected == true)
    {
        g.setColour(Colours::green);
    }
    else if(rowNumber % 2 == 0)
    {
        g.setColour(Colours::lightblue);
    }
    else if(rowNumber % 2 != 0)
    {
        g.setColour(Colours::orange);
    }
    
    g.fillAll();
}

void QueueTableModel::paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected)
{
    String stringToDraw;
    
    if(columnId == 1)
    {
        stringToDraw = String(items[rowNumber - 1].getItemIndex());
    }
    
    else if(columnId == 2)
    {
        stringToDraw = items[rowNumber - 1].getFileName();
    }
    
    else if(columnId == 3)
    {
        stringToDraw = String(items[rowNumber - 1].getFileSize());
    }
    
    else if(columnId == 4)
    {
        stringToDraw = items[rowNumber - 1].getLengthInTime();
    }
    
    g.drawText(stringToDraw, 0, 0, width, height, Justification::centred);
}

Component* QueueTableModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if(columnId == 5)
    {
        return items[rowNumber - 1].getPlayTimeLabel();
    }
    
    else if(columnId == 6)
    {
        return items[rowNumber - 1].getStopTimeLabel();
    }
    
    else if(columnId == 7)
    {
        return items[rowNumber - 1].getPlayButton();
    }
    
    else
    {
        return nullptr;
    }
}
