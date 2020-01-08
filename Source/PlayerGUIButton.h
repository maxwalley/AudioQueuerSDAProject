/*
  ==============================================================================

    PlayControlButton.h
    Created: 22 Dec 2019 6:58:56pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PlayerGUIButton    : public Button
{
public:
    PlayerGUIButton(PlayerControl buttonFunc);
    ~PlayerGUIButton();

    void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    enum PlayerControl
    {
        stop,
        next,
        last
    };
    
private:
    
    PlayerControl control;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerGUIButton)
};
