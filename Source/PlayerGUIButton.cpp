/*
  ==============================================================================

    PlayControlButton.cpp
    Created: 22 Dec 2019 6:58:56pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayerGUIButton.h"

//==============================================================================
PlayerGUIButton::PlayerGUIButton(ControlType function) : Button("")
{
    buttonFunc = function;
}

PlayerGUIButton::~PlayerGUIButton()
{
}

void PlayerGUIButton::paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    g.setColour(Colours::white);
    
    g.fillEllipse(0, 0, getWidth(), getHeight());
    g.setColour(Colours::black);
    
    Path path;
    
    if(buttonFunc == play)
    {
        path.addTriangle(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2, (getWidth()/3) * 2, getHeight()/2);
    }
    
    else if(buttonFunc == pause)
    {
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine((getWidth()/3) * 1.5, getHeight()/3, (getWidth()/3) * 1.5, (getHeight()/3) * 2);
    }
    
    else if(buttonFunc == stop)
    {
        g.fillRect(getWidth()/3, getHeight()/3, getWidth()/3, getHeight()/3);
    }
    
    else if(buttonFunc == next)
    {
        path.addTriangle(getWidth()/3, getHeight()/3, (getWidth()/3) * 2, getHeight()/2, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine((getWidth()/3) * 2, getHeight()/3, (getWidth()/3) * 2, (getHeight()/3) * 2);
    }
    
    else if(buttonFunc == last)
    {
        path.addTriangle(getWidth()/3, getHeight()/2, (getWidth()/3) * 2, getHeight()/3, (getWidth()/3) * 2, (getHeight()/3) * 2);
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
    }
    
    g.fillPath(path);
}

void PlayerGUIButton::changeFunction(ControlType newFunction)
{
    buttonFunc = newFunction;
    repaint();
}

int PlayerGUIButton::getFunction() const
{
    return buttonFunc;
}
