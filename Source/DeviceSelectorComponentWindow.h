/*
  ==============================================================================

    DeviceSelectorComponent.h
    Created: 16 Jan 2020 12:23:07pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeviceSelectorWindow.h"

//==============================================================================
/*
*/
class DeviceSelectorComponentWindow    : public Component
{
public:
    /**
    Constructor
    
    @param deviceManager   The device manager that this component should control
    */
    DeviceSelectorComponentWindow(AudioDeviceManager &deviceManager);
    ~DeviceSelectorComponentWindow();

    void paint (Graphics&) override;
    void resized() override;

private:
    
    AudioDeviceSelectorComponent deviceSelector;
    
    std::unique_ptr<DocumentWindow> devSelWindow;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeviceSelectorComponentWindow)
};
