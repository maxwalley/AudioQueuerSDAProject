/*
  ==============================================================================

    ComponentWindow.h
    Created: 16 Jan 2020 1:29:57pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class ComponentWindow    : public DocumentWindow,
                           public ActionBroadcaster
{
public:
    ComponentWindow(const String &name, Colour backgroundColour, int requiredButtons);
    ~ComponentWindow();


private:
    
    void closeButtonPressed() override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ComponentWindow)
};
