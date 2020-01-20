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
    enum ControlType
    {
        play,
        pause,
        stop,
        next,
        last
    };
    
    //Contructor sort this
    PlayerGUIButton(ControlType function);
    
    /**Destructor*/
    ~PlayerGUIButton();

    /**Implementation of the Component method*/
    void paintButton (Graphics &g, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override;
    
    void changeFunction(ControlType newFunction);
    
    int getFunction() const;
    
private:
    
    ControlType buttonFunc;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlayerGUIButton)
};
