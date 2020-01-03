/*
  ==============================================================================

    LoopToggleButton.cpp
    Created: 3 Jan 2020 12:36:37pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "LoopToggleButton.h"

//==============================================================================
LoopToggleButton::LoopToggleButton()
{
    setClickingTogglesState(true);
}

LoopToggleButton::~LoopToggleButton()
{
    
}

void LoopToggleButton::paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    g.setColour(Colours::black);
    
    g.drawRoundedRectangle(0, 0, getWidth(), getHeight(), 6, 2);
    
    if(shouldDrawButtonAsDown == true)
    {
        g.drawLine((getWidth()/4) * 3, (getHeight()/3), getWidth()/2, (getHeight()/4) * 3, 2);
        g.drawLine(getWidth()/2, (getHeight()/4) * 3, getWidth()/4, getHeight()/2, 2);
    }
}
