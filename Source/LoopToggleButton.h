/*
  ==============================================================================

    LoopToggleButton.h
    Created: 3 Jan 2020 12:36:37pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class LoopToggleButton    : public ToggleButton
{
public:
    LoopToggleButton();
    ~LoopToggleButton();

    void paintButton(Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LoopToggleButton)
};
