/*
  ==============================================================================

    QueueTableHeader.h
    Created: 19 Nov 2019 5:01:29pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/** Class that acts as the header for the TableListBox in the AudioTable class.
*/
class QueueTableHeader    : public TableHeaderComponent
{
public:
    /**Constructor*/
    QueueTableHeader();
    
    /**Destructor*/
    ~QueueTableHeader();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueTableHeader)
};
