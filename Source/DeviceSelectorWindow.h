/*
  ==============================================================================

    DeviceSelectorWindow.h
    Created: 19 Dec 2019 7:30:09pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class DeviceSelectorWindow    : public Component
{
public:
    DeviceSelectorWindow(AudioDeviceManager &deviceManager);
    ~DeviceSelectorWindow();

    void paint (Graphics&) override;
    void resized() override;

    void showWindow(bool show);
    
private:
    
    AudioDeviceSelectorComponent deviceSelector;
    
    DocumentWindow selectorWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeviceSelectorWindow)
};
