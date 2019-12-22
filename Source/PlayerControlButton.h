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
class PlayerControlButton    : public Button
{
public:
    enum Function
    {
        stop,
        next,
        last
    };
    
    PlayerControlButton(Function function);
    ~PlayerControlButton();

    void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    
    Function buttonFunc;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerControlButton)
};
