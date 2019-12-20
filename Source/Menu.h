/*
  ==============================================================================

    Menu.h
    Created: 19 Dec 2019 7:02:48pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "DeviceSelectorWindow.h"

//==============================================================================
/*
*/
class Menu    : public MenuBarModel,
                public Component
{
public:
    Menu(AudioDeviceManager* devManager);
    ~Menu();

    void paint (Graphics&) override;
    void resized() override;

private:
    MenuBarComponent menu;
    
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
    DeviceSelectorWindow deviceSelectorWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Menu)
};
