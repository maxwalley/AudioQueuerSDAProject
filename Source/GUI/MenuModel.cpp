/*
  ==============================================================================

    MenuModel.cpp
    Created: 12 Nov 2019 12:00:15am
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../../JuceLibraryCode/JuceHeader.h"
#include "MenuModel.h"

//==============================================================================
MenuModel::MenuModel()
{
    
}

MenuModel::~MenuModel()
{
    
}

StringArray MenuModel::getMenuBarNames()
{
    const char* const names[] = { "File", 0 };
    return StringArray (names);
}

PopupMenu MenuModel::getMenuForIndex(int topLevelMenuIndex, const String &menuName)
{
    PopupMenu menu;
    
    if (topLevelMenuIndex == 0)
    {
        menu.addItem(1, "Audio Prefrences", true, false);
        menu.addItem(2, "Open File", true, false);
    }
    
    return menu;
}

void MenuModel::menuItemSelected(int menuItemID, int topLevelMenuIndex)
{
    if(topLevelMenuIndex == 0)
    {
        if (menuItemID == 1)
        {
            DBG("AUDIO PREFS CLICKED");
        }
        else if (menuItemID == 2)
        {
            
        }
    }
}
