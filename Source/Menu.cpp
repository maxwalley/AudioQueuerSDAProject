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
Menu::Menu(AudioDeviceManager &devManager) : selectorWindow(devManager)
{
    setMacMainMenu(this);
}

Menu::~Menu()
{
}

StringArray Menu::getMenuBarNames()
{
    //List of menu titles
    const char* const names[] = { "File", "Audio", "Queue", 0 };
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
    
    //Queue tab
    else if(topLevelMenuIndex == 2)
    {
        menu.addItem(1, "Loop Queue", true, false);
        menu.addItem(2, "Shuffle Queue", true, false);
        menu.addItem(3, "Play Continuously", true, false);
    }
    
    return menu;
}

void Menu::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    if(topLevelMenuIndex == 0)
    {
        if(menuItemID == 1)
        {
            selectorWindow.showWindow(true);
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
            sendActionMessage("Pause audio");
        }
        
        else if(menuItemID == 3)
        {
            sendActionMessage("Stop audio");
        }
    }
    
    else if(topLevelMenuIndex == 2)
    {
        if(menuItemID == 1)
        {
            sendActionMessage("Loop Queue Clicked");
        }
        
        else if(menuItemID == 2)
        {
            sendActionMessage("Shuffle Queue Clicked");
        }
        
        else if(menuItemID == 3)
        {
            sendActionMessage("Continous Control Clicked");
        }
    }
}
