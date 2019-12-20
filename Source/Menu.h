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
                public ActionBroadcaster
{
public:
    Menu(AudioDeviceManager* devManager);
    ~Menu();
    
    /**Changes what menu items are enabled*/
    void changeEnabledItems();

private:
    /**Overriden from MenuBarModel
     Returns a list of the menu bar names as a string array*/
    StringArray getMenuBarNames() override;
    
    /**Overriden from MenuBarModel
     Returns the PopupMenu to display for a given top level menu
     Parameters:
        topLevelMenuIndex = The index of the top level menu to show
        menuName = The name of the top level menu to show*/
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    
    /**Overriden from MenuBarModel
     This is called when a menu item has been clicked on.
     Parameters:
        menuItemID = The item ID of the PopupMenu item that was selected
        topLevelMenuIndex = the index of the top-level menu from which the item was chosen (just in case you've used duplicate ID numbers on more than one of the popup menus)*/
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
    //DeviceSelectorWindow deviceSelectorWindow;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Menu)
};
