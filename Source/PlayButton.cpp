/*
  ==============================================================================

    PlayButton.cpp
    Created: 19 Nov 2019 8:16:43pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayButton.h"

//==============================================================================
PlayButton::PlayButton() : Button (String())
{
    //setSize(15, 15);
    setClickingTogglesState(true);
    setToggleState(false, dontSendNotification);
}

PlayButton::~PlayButton()
{
}

void PlayButton::paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    //Draws triangle
    g.drawLine(getWidth()/3, 0, getWidth()/3, getHeight());
    g.drawLine(getWidth()/3, 0, getWidth()/3, getHeight()/2);
    g.drawLine(getWidth()/3 , getHeight(), getWidth(),3, getHeight()/2);
}
