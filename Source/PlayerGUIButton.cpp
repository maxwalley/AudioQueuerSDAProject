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
    //Draws a circle
    g.setColour(Colours::white);
    g.fillEllipse(0, 0, getWidth(), getHeight());
    
    g.setColour(Colours::black);
    
    Path path;
    
    //Checks what the intended button function is and draws its contents based on that
    if(buttonFunc == play)
    {
        //Draws a triangle
        path.addTriangle(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2, (getWidth()/3) * 2, getHeight()/2);
    }
    
    else if(buttonFunc == pause)
    {
        //Draws 2 lines
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine((getWidth()/3) * 1.5, getHeight()/3, (getWidth()/3) * 1.5, (getHeight()/3) * 2);
    }
    
    else if(buttonFunc == stop)
    {
        //Draws a rectangle
        g.fillRect(getWidth()/3, getHeight()/3, getWidth()/3, getHeight()/3);
    }
    
    else if(buttonFunc == next)
    {
        //Draws a forward facing triangle with a line at the point
        path.addTriangle(getWidth()/3, getHeight()/3, (getWidth()/3) * 2, getHeight()/2, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine((getWidth()/3) * 2, getHeight()/3, (getWidth()/3) * 2, (getHeight()/3) * 2);
    }
    
    else if(buttonFunc == last)
    {
        //Draws a backward facing triangle with a line at the point
        path.addTriangle(getWidth()/3, getHeight()/2, (getWidth()/3) * 2, getHeight()/3, (getWidth()/3) * 2, (getHeight()/3) * 2);
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
    }
    
    g.fillPath(path);
}

void PlayerGUIButton::changeFunction(ControlType newFunction)
{
    //Sets the new function then repaints the entire button
    buttonFunc = newFunction;
    repaint();
}

int PlayerGUIButton::getFunction() const
{
    return buttonFunc;
}
