/*
  ==============================================================================

    ComponentWindow.cpp
    Created: 16 Jan 2020 1:29:57pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "ComponentWindow.h"

//==============================================================================
ComponentWindow::ComponentWindow(const String &name, Colour backgroundColour, int requiredButtons) : DocumentWindow(name, backgroundColour, requiredButtons)
{
    setUsingNativeTitleBar(true);
}

ComponentWindow::~ComponentWindow()
{
    
}

void ComponentWindow::closeButtonPressed()
{
    setContentOwned(nullptr, false);
    //sendActionMessage("Deleting window");
    delete this;
}
