/*
  ==============================================================================

    ColourSelectorWindow.cpp
    Created: 23 Jan 2020 5:28:25pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ColourSelectorWindow.h"

//==============================================================================
ColourSelectorWindow::ColourSelectorWindow(const String &name, Colour backgroundColour, int requiredButtons) : ComponentWindow(name, backgroundColour, requiredButtons)
{
    selector.setSize(getWidth(), getHeight());
    selector.addMouseListener(this, true);
    
    //Sets the windows content to the ColourSelector component
    setContentOwned(&selector, true);
}

ColourSelectorWindow::~ColourSelectorWindow()
{
    
}

Colour ColourSelectorWindow::getColour() const
{
    return selector.getCurrentColour();
}
