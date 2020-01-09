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
PlayPauseButton::PlayPauseButton(ControlType function) : PlayerGUIButton(PlayerGUIButton::stop)
{
    
}

PlayPauseButton::~PlayPauseButton()
{
}

void PlayPauseButton::paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    /*g.setColour(Colours::white);
    g.fillEllipse(0, 0, getWidth(), getHeight());
    
    g.setColour(Colours::black);
    
    if(buttonState == play)
    {
        Path path;
        
        path.startNewSubPath(getWidth()/3, getHeight()/3);
        path.lineTo(getWidth()/3, (getHeight()/3) * 2);
        path.lineTo((getWidth()/3) * 2, getHeight()/2);
        path.closeSubPath();
        
        g.fillPath(path);
    }
    else if(buttonState == pause)
    {
        g.drawLine(getWidth()/3, getHeight()/3, getWidth()/3, (getHeight()/3) * 2);
        g.drawLine((getWidth()/3) * 1.5, getHeight()/3, (getWidth()/3) * 1.5, (getHeight()/3) * 2);
    }*/
}

/*void PlayPauseButton::changeState(bool newState)
{
    if(newState == 0 && buttonState == pause)
    {
        buttonState = play;
    }
    else if(newState == 1 && buttonState == play)
    {
        buttonState = pause;
    }
    
    repaint();
}

int PlayPauseButton::getButtonState()
{
    return buttonState;
}*/
