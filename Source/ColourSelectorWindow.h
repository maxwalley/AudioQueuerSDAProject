/*
  ==============================================================================

    ColourSelectorWindow.h
    Created: 23 Jan 2020 5:28:25pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ComponentWindow.h" 

//==============================================================================
/** A ComponentWindow that holds a ColourSelector component. Sends an action message when the window is clicked or the mouse is released however to implement this the owned component must have this as a mouse listener. You can then call getColour() to find the colour the user selected
*/
class ColourSelectorWindow    : public ComponentWindow
{
public:
    /**Constructor
     
     @param name            the name of the window
     @param backgroundColour            the background colour of the window
     @param requiredButtons         the buttons to put in the top left hand corner of the window
     
     @see DocumentWindow()
     */
    ColourSelectorWindow(const String &name, Colour backgroundColour, int requiredButtons);
    
    /**Destructor*/
    ~ColourSelectorWindow();
    
    /**Returns the colour currently selected by the user
     
     @return the colour currently selected
     */
    Colour getColour() const;

private:
    ColourSelector selector;
    String windowName;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ColourSelectorWindow)
};
