/*
  ==============================================================================

    QueueTable.h
    Created: 19 Nov 2019 4:50:39pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueTableHeader.h"
#include "QueueTableModel.h"

//==============================================================================
/*
*/
class QueueTable    : public TableListBox
{
public:
    QueueTable();
    ~QueueTable();

    void paint (Graphics&) override;
    void resized() override;
    
    void addItem(File* file);

private:
    
    QueueTableHeader header;
    QueueTableModel model;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueTable)
};
