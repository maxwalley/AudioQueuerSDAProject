/*
  ==============================================================================

    InfoSection.h
    Created: 14 Dec 2019 7:56:01pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class InfoSection    : public Component
{
public:
    InfoSection(String description);
    ~InfoSection();

    void paint (Graphics&) override;
    void resized() override;

    /**Sets the data of the section*/
    void setData(String data);
    
private:
    /**Holds the description of the data of the section*/
    Label descriptorLabel;
    
    /**Holds the data of the section*/
    Label dataLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoSection)
};
