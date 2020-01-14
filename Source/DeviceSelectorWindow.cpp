/*
  ==============================================================================

    DeviceSelectorWindow.cpp
    Created: 19 Dec 2019 7:30:09pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeviceSelectorWindow.h"

//==============================================================================
DeviceSelectorWindow::DeviceSelectorWindow(AudioDeviceManager &deviceManager) : deviceSelector(deviceManager, 0, 0, 0, 2, false, false, true, false), selectorWindow("Audio Device Selector", Colours::grey, DocumentWindow::allButtons)
{
    setSize(350, 200);
    addAndMakeVisible(deviceSelector);
    deviceSelector.setSize(350, 200);
    
    selectorWindow.setContentOwned(this, true);
    selectorWindow.setSize(350, 200);
    selectorWindow.setUsingNativeTitleBar(true);
    
}

DeviceSelectorWindow::~DeviceSelectorWindow()
{
}

void DeviceSelectorWindow::showWindow(bool show)
{
    if(show == true)
    {
        selectorWindow.setVisible(true);
    }
    else
    {
        selectorWindow.setVisible(false);
    }
}
