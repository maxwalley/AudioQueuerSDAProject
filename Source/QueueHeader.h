/*
  ==============================================================================

    QueueHeader.h
    Created: 16 Nov 2019 7:57:37pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class QueueHeader    : public Component
{
public:
    QueueHeader();
    ~QueueHeader();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueHeader)
};
