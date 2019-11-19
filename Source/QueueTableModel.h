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

//==============================================================================
/*
*/
class QueueTableModel    : public TableListBoxModel
{
public:
    QueueTableModel();
    ~QueueTableModel();

private:
    
    Array<QueueItem> items;
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueTableModel)
};
