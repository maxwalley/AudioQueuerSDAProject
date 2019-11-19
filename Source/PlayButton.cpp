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
    setSize(15, 15);
    setClickingTogglesState(true);
    setToggleState(false, dontSendNotification);
}

PlayButton::~PlayButton()
{
}

void PlayButton::paint (Graphics& g)
{
    g.drawLine(0, 0, 15, 7.5);
    g.drawLine(0, 0, 0, 15);
    g.drawLine(0, 15, 15, 7.5);
}
