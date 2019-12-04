/*
  ==============================================================================

    QueueTableModel.h
    Created: 19 Nov 2019 4:50:50pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueItem.h"
#include "QueueTableHeader.h"

//==============================================================================
/*
*/
class QueueTableModel    : public TableListBoxModel,
                           public Component,
                            public ActionBroadcaster
{
public:
    QueueTableModel();
    ~QueueTableModel();
    
    void resized() override;
    
    TableListBox embeddedTable;
    
    Array<QueueItem*> items;
    AudioTransportSource transport;

    void addNewItem(File* file);
    
    int getSelectedRow();
    File* getSelectedFile();
    
    void moveTransportOn();
    
    void startQueue();
    
private:
    
    //Array<QueueItem*> items;
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;

    void selectedRowsChanged(int lastRowSelected) override;
    
    QueueTableHeader header;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueTableModel)
};
