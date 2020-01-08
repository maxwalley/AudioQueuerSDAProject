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
PlayerGUIButton::PlayerGUIButton() : Button("")
{
    //setColour(TextButton::buttonColourId, Colours::white);
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
    
    if(buttonFunc == stop)
    {
        g.fillRect(getWidth()/3, getHeight()/3, getWidth()/3, getHeight()/3);
    }
    
    else if(buttonFunc == next)
    {
        g.drawLine((getWidth()/3) * 2, getHeight()/3, (getWidth()/3) * 2, (getHeight()/3) * 2);
        
        path.startNewSubPath(getWidth()/3, getHeight()/3);
        path.lineTo(getWidth()/3, (getHeight()/3) * 2);
        path.lineTo((getWidth()/3) * 2, getHeight()/2);
        path.closeSubPath();
    }
    
    else if(buttonFunc == last)
    {
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
        
        path.startNewSubPath((getWidth()/3) * 2, getHeight()/3);
        path.lineTo((getWidth()/3) * 2, (getHeight()/3) * 2);
        path.lineTo(getWidth()/3, getHeight()/2);
        path.closeSubPath();
    }
    
    g.fillPath(image);
}

