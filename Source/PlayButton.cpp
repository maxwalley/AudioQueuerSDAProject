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
    setClickingTogglesState(true);
    setToggleState(false, dontSendNotification);
}

PlayButton::~PlayButton()
{
    
}

void PlayButton::paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown)
{
    //Draws triangle
    g.drawLine(2, 0, 2, getHeight(),2);
    g.drawLine(2, 0, getWidth(), getHeight()/2,2);
    g.drawLine(2, getHeight(), getWidth(), getHeight()/2,2);
}
