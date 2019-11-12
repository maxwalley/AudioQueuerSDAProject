/*
  ==============================================================================

    MenuModel.h
    Created: 12 Nov 2019 12:00:15am
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class MenuModel    : public MenuBarModel
{
public:
    MenuModel();
    ~MenuModel();

    //==============================================================================
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MenuModel)
};
