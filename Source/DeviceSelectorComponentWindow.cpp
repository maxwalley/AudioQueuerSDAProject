/*
  ==============================================================================

    DeviceSelectorComponent.cpp
    Created: 16 Jan 2020 12:23:07pm
    Author:  Max Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
DeviceSelectorComponentWindow::DeviceSelectorComponentWindow(AudioDeviceManager &deviceManager) : deviceSelector(deviceManager, 0, 0, 0, 2, false, false, true, false)
{
    setSize(150, 300);
}

DeviceSelectorComponentWindow::~DeviceSelectorComponentWindow()
{
}

void DeviceSelectorComponentWindow::paint (Graphics& g)
{
    
}

void DeviceSelectorComponentWindow::resized()
{
    
}
