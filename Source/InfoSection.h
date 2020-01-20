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
    /**Implementation of the LookAndFeel_V4 method*/
    void drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& ) override;
};


class InfoSection    : public Component
{
public:
    /**Constructor
     
     @param description         the text to put in the description TextEditor
     */
    InfoSection(String description);
    
    /**Destructor*/
    ~InfoSection();

    /**Implementation of the Component method*/
    void paint(Graphics& g) override;
    
    /**Implementation of the Component method*/
    void paintOverChildren(Graphics& g) override;
    
    /**Implementation of the Component method*/
    void resized() override;

    /**Sets the text in the data TextEditor
     
     @param data            the text to put in the data TextEditor
     */
    void setData(String data);
    
private:
    TextEditorLookAndFeel editorLookAndFeel;
    
    /**Holds the description of the data of the section*/
    TextEditor descriptorText;
    
    /**Holds the data of the section*/
    TextEditor dataText;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoSection)
};
