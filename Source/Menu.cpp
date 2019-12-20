/*
  ==============================================================================

    Menu.cpp
    Created: 19 Dec 2019 7:02:48pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Menu.h"

//==============================================================================
Menu::Menu(AudioDeviceManager* devManager) //: deviceSelectorWindow(devManager)
{
    //setSize(1100, 20);
    
    setMacMainMenu(this);
    
    //addAndMakeVisible(menu);
    //menu.setModel(this);
}

Menu::~Menu()
{
}

void Menu::paint (Graphics& g)
{
    
}

void Menu::resized()
{
    menu.setBounds(0, 0, 1100, 20);
}

StringArray Menu::getMenuBarNames()
{
    //List of menu titles
    const char* const names[] = { "File", "Audio", 0 };
    return StringArray (names);
}

PopupMenu Menu::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    //File tab
    if(topLevelMenuIndex == 0)
    {
        menu.addItem(1, "Audio Prefrences", true, false);
        menu.addItem(2, "Add File to Queue", true, false);
    }
    
    //Audio tab
    else if(topLevelMenuIndex == 1)
    {
        menu.addItem(1, "Play Queue", true, false);
        menu.addItem(2, "Pause", true, false);
        menu.addItem(3, "Stop", true, false);
    }
    
    return menu;
}

void Menu::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    if(topLevelMenuIndex == 0)
    {
        if(menuItemID == 1)
        {
            DBG("AUDIO PREFS CLICKED");
            //deviceSelectorWindow.setVisible(true);
        }
        else if(menuItemID == 2)
        {
            sendActionMessage("Add file");
        }
    }
    
    else if(topLevelMenuIndex == 1)
    {
        if(menuItemID == 1)
        {
            sendActionMessage("Play queue");
        }
        
        else if(menuItemID == 2)
        {
            sendActionMessage("Pause Audio");
        }
        
        else if(menuItemID == 3)
        {
            sendActionMessage("Stop Audio");
        }
    }
}
