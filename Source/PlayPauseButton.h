/*
  ==============================================================================

    PlayPauseButton.h
    Created: 22 Dec 2019 4:57:43pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayerGUIButton.h"

//==============================================================================
/*
*/

class PlayPauseButton    : public PlayerGUIButton
{
public:
    enum ControlType
    {
        play,
        pause,
        stop,
        next,
        last
    };
    
    PlayPauseButton(ControlType function);
    ~PlayPauseButton();

    void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    /**Causes the button to change its state to a selected new state
     0 for play
     1 for pause*/
    //void changeState(bool newState);
    
    /**Returns the current state of the button*/
    //int getButtonState();
private:
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayPauseButton)
};
