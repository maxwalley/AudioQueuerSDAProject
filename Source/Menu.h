/*
  ==============================================================================

    Menu.h
    Created: 19 Dec 2019 7:02:48pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ComponentWindow.h"

//==============================================================================
/*
*/
class Menu    : public MenuBarModel,
                public ActionBroadcaster
{
public:
    /**Constructor
     
     @param devManager          The audio device manager the audio system is using
     */
    Menu(AudioDeviceManager &devManager);
    
    /**Destructor*/
    ~Menu();

private:
    /**Implementation of the MenuBarModel method*/
    StringArray getMenuBarNames() override;
    
    /**Implementation of the MenuBarModel method*/
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    
    /**Implementation of the MenuBarModel method*/
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
    bool queueLoop;
    bool queueShuffle;
    
    Component::SafePointer<ComponentWindow> selectorWindow;
    
    AudioDeviceManager* deviceManager;
    Component::SafePointer<AudioDeviceSelectorComponent> selector;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Menu)
};
