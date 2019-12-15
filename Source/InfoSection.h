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
class TextEditorLookAndFeel : public LookAndFeel_V4
{
private:
    /**Overidden from TextEditor::LookAndFeelMethods
     Allows the outline of the text editor to be redrawn*/
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& ) override;
};


class InfoSection    : public Component
{
public:
    InfoSection(String description);
    ~InfoSection();

    void paintOverChildren (Graphics&) override;
    void resized() override;

    /**Sets the data of the section*/
    void setData(String data);
    
private:
    /**Holds the description of the data of the section*/
    TextEditor descriptorText;
    
    /**Holds the data of the section*/
    TextEditor dataText;
    
    TextEditorLookAndFeel editorLookAndFeel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoSection)
};
