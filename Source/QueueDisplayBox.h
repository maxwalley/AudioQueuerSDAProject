/*
  ==============================================================================

    QueueDisplayBox.h
    Created: 12 Nov 2019 9:58:58pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueItem.h"
#include "QueueHeader.h"

//==============================================================================
/*
*/
class QueueDisplayBox    : public Component
{
public:
    QueueDisplayBox();
    ~QueueDisplayBox();

    void paint (Graphics&) override;
    void resized() override;

    void addNewItem(File* file);
private:
    Rectangle<int> mainDisplay;
    
    Array<QueueItem* ,CriticalSection> items;
    
    int numItems;
    
    int selectedItem;
    
    QueueHeader header;
    
    void mouseDown(const MouseEvent &event) override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueDisplayBox)
};
