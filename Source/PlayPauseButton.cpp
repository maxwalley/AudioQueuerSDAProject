/*
  ==============================================================================

    PlayPauseButton.cpp
    Created: 22 Dec 2019 4:57:43pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayPauseButton.h"

//==============================================================================
PlayPauseButton::PlayPauseButton() : Button(""), buttonState(play)
{
    
}

PlayPauseButton::~PlayPauseButton()
{
}

void PlayPauseButton::paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    g.setColour(Colours::white);
    g.fillEllipse(0, 0, getWidth(), getHeight());
    
    g.setColour(Colours::black);
    
    if(buttonState == play)
    {
        //Draws triangle
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2, 2);
        g.drawLine(getWidth()/3, getHeight()/3, (getWidth()/3) * 2, getHeight()/2, 2);
        g.drawLine(getWidth()/3, (getHeight()/3) * 2, (getWidth()/3) * 2, getHeight()/2, 2);
    }
    else if(buttonState == pause)
    {
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine((getWidth()/3) * 1.5, getHeight()/3, (getWidth()/3) * 1.5, (getHeight()/3) * 2);
    }
}

void PlayPauseButton::changeState()
{
    switch(buttonState)
    {
        case play:
            buttonState = pause;
            break;
            
        case pause:
            buttonState = play;
            break;
    }
    repaint();
}

int PlayPauseButton::getButtonState()
{
    return buttonState;
}
