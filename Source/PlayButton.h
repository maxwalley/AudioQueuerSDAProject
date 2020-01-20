/*
  ==============================================================================

    PlayButton.h
    Created: 19 Nov 2019 8:16:43pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class PlayButton    : public Button
{
public:
    /**Constructor*/
    PlayButton();
    
    /**Destructor*/
    ~PlayButton();

    /**Implementation of the Button method*/
    void paintButton (Graphics& g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayButton)
};
