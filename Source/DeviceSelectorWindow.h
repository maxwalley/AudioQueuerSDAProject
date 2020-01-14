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
    /**
     Constructor
     
     @param deviceManager   The device manager that this component should control
     */
    DeviceSelectorWindow(AudioDeviceManager &deviceManager);
    
    /**
     Destructor
     */
    ~DeviceSelectorWindow();

    /**
     Sets whether the window is shown or not
     
     @param show   Whether to show the window or not
     */
    void showWindow(bool show);
    
private:
    
    AudioDeviceSelectorComponent deviceSelector;
    
    DocumentWindow selectorWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DeviceSelectorWindow)
};
