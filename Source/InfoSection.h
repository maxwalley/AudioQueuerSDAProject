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
/** A class to control the look of an info section
*/
class TextEditorLookAndFeel : public LookAndFeel_V4
{
private:
    /**Implementation of the LookAndFeel_V4 method*/
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& ) override;
};

/** A component class that makes up a section of the InfoBox component class. Holds two TextEditors. One holding data and the other holding a description of the data. Set the data with setData().
*/
class InfoSection    : public Component
{
public:
    /**Constructor
     
     @param description         the text to put in the description TextEditor
     */
    InfoSection(String description);
    
    /**Destructor*/
    ~InfoSection();

    /**Implementation of the JUCE Component method*/
    void paint(Graphics& g) override;
    
    /**Implementation of the JUCE Component method*/
    void paintOverChildren(Graphics& g) override;
    
    /**Implementation of the JUCE Component method*/
    void resized() override;

    /**Sets the text in the data TextEditor
     
     @param data            the text to put in the data TextEditor
     */
    void setData(String data);
    
    /**Clears both TextEditors*/
    void clear();
    
private:
    TextEditorLookAndFeel editorLookAndFeel;
    
    /**Holds the description of the data of the section*/
    TextEditor descriptorText;
    
    /**Holds the data of the section*/
    TextEditor dataText;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoSection)
};
