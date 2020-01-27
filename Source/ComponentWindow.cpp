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
    windowName = name;
    
    setUsingNativeTitleBar(true);
}

ComponentWindow::~ComponentWindow()
{
    
}

void ComponentWindow::closeButtonPressed()
{
    delete this;
}

void ComponentWindow::mouseDown(const MouseEvent &event)
{
    //Sends this message if the mouse is clicked on the window
    sendActionMessage("Mouse Clicked on " + windowName);
}

void ComponentWindow::mouseUp(const MouseEvent &event)
{
    //Sends this message if the mouse is released on the window
    sendActionMessage("Mouse Released on " + windowName);
}
