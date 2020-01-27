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
    //Path drawing the triangle of a play button then filling it in
    Path path;
    path.startNewSubPath(2, 0);
    path.lineTo(2, getHeight());
    path.lineTo(getHeight(), getHeight()/2);
    path.closeSubPath();
    
    g.fillPath(path);
}
