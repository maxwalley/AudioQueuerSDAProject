/*
  ==============================================================================

    PlayControlButton.cpp
    Created: 22 Dec 2019 6:58:56pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayerControlButton.h"

//==============================================================================
PlayerControlButton::PlayerControlButton(Function function) : Button("")
{
    buttonFunc = function;
    
    setColour(TextButton::buttonColourId, Colours::white);
}

PlayerControlButton::~PlayerControlButton()
{
}

void PlayerControlButton::paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    g.setColour(Colours::white);
    
    g.fillEllipse(0, 0, getWidth(), getHeight());
    g.setColour(Colours::black);
    
    if(buttonFunc == stop)
    {
        g.drawRect(getWidth()/3, getHeight()/3, getWidth()/3, getHeight()/3);
    }
    
    else if(buttonFunc == next)
    {
        g.drawLine((getWidth()/3) * 2, getHeight()/3, (getWidth()/3) * 2, (getHeight()/3) * 2);
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine(getWidth()/3, getHeight()/3, (getWidth()/3) * 2, getHeight()/2);
        g.drawLine(getWidth()/3, (getHeight()/3) * 2, (getWidth()/3) * 2, getHeight()/2);
    }
    
    else if(buttonFunc == last)
    {
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine(getWidth()/3, getHeight()/2, (getWidth()/3) * 2, getHeight()/3);
        g.drawLine(getWidth()/3, getHeight()/2, (getWidth()/3) * 2, (getHeight()/3) * 2);
        g.drawLine((getWidth()/3) * 2, getHeight()/3, (getWidth()/3) * 2, (getHeight()/3) * 2);
    }
}
