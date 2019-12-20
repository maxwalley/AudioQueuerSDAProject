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
DeviceSelectorWindow::DeviceSelectorWindow(AudioDeviceManager* devManager) : DocumentWindow("Audio Device Selector", Colours::palegreen, 7), deviceSelector(*devManager, 0, 0, 1, 2, false, false, true, true)
{
    setSize(500, 500);
    
    addAndMakeVisible(&deviceSelector);
}

DeviceSelectorWindow::~DeviceSelectorWindow()
{
}

void DeviceSelectorWindow::paint (Graphics& g)
{
    
}

void DeviceSelectorWindow::resized()
{
    deviceSelector.setBounds(0, 0, getWidth(), getHeight());
}
