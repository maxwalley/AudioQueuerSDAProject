/*
  ==============================================================================

    PlayPauseButton.h
    Created: 22 Dec 2019 4:57:43pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/

class PlayPauseButton    : public Button
{
public:
    PlayPauseButton();
    ~PlayPauseButton();

    void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

    void changeState();
    
    /**Returns the current state of the button*/
    int getButtonState();
private:
    
    enum State
    {
        play,
        pause
    };
    
    State buttonState;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayPauseButton)
};
