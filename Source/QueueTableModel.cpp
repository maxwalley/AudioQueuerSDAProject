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
    addAndMakeVisible(embeddedTable);
    
    embeddedTable.setHeader(&header);
    embeddedTable.setModel(this);
    
    items.clear();
}

QueueTableModel::~QueueTableModel()
{
    for(int i = 0; i < items.size(); i++)
    {
        delete items[i];
    }
}

void QueueTableModel::resized()
{
    embeddedTable.setBounds(0, 0, getWidth(), getHeight());
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
        stringToDraw = String(items[rowNumber]->getItemIndex());
    }
    
    else if(columnId == 2)
    {
        stringToDraw = items[rowNumber]->getFileName();
    }
    
    else if(columnId == 3)
    {
        stringToDraw = String(items[rowNumber]->getFileSize());
    }
    
    else if(columnId == 4)
    {
        stringToDraw = items[rowNumber]->getLengthInTime();
    }
    
    g.setColour(Colours::black);
    g.drawText(stringToDraw, 0, 0, width, height, Justification::centred);
    
    /*if (columnId == 2)
    {
        g.setColour(Colours::black);
        g.drawText("Hello", 0, 0, width, height, Justification::centred);
    }*/
}

Component* QueueTableModel::refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate)
{
    if(columnId == 5)
    {
        return items[rowNumber]->getPlayTimeLabel();
    }
    
    else if(columnId == 6)
    {
        return items[rowNumber]->getStopTimeLabel();
    }
    
    else if(columnId == 7)
    {
        return items[rowNumber]->getPlayButton();
    }
    
    else
    {
        return nullptr;
    }
}

void QueueTableModel::addNewItem(File* file)
{
    int currentNumFiles = items.size() + 1;
    
    QueueItem* newItem = new QueueItem(currentNumFiles, file);
    
    items.add(newItem);

    embeddedTable.updateContent();
}

void QueueTableModel::selectedRowsChanged(int lastRowSelected)
{
    transport.setSource(items[lastRowSelected]->audioFormatReaderSource.get(), 0, nullptr, items[lastRowSelected]->getReaderSampleRate(), items[lastRowSelected]->getReaderNumChannels());
    sendActionMessage("Selected Row Changed");
}

int QueueTableModel::getSelectedRow()
{
    return embeddedTable.getSelectedRow();
}

File* QueueTableModel::getSelectedFile()
{
    int selectedRowNum = getSelectedRow();
    return items[selectedRowNum]->getFile();
}

void QueueTableModel::moveTransportOn()
{
    int selectedRowNum = getSelectedRow();
    embeddedTable.selectRow(selectedRowNum + 1, true, true);
}
