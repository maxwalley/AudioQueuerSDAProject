/*
  ==============================================================================

    InfoSection.cpp
    Created: 14 Dec 2019 7:56:01pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "InfoSection.h"

//==============================================================================
InfoSection::InfoSection(String description)
{
    //Sets some as smaller than others
    if(description == "File Size (Bytes)" || description == "File Length" || description == "Sample Rate")
    {
        setSize(200, 25);
    }
    else
    {
        setSize(200, 50);
    }
    
    addAndMakeVisible(descriptorText);
    
    addAndMakeVisible(dataText);
    
    descriptorText.setLookAndFeel(&editorLookAndFeel);
    dataText.setLookAndFeel(&editorLookAndFeel);
    
    descriptorText.setReadOnly(true);
    dataText.setReadOnly(true);
    
    descriptorText.setMultiLine(true);
    dataText.setMultiLine(true);
    
    descriptorText.setText(description);
    dataText.setText("");
}

InfoSection::~InfoSection()
{
    
}

void InfoSection::paint(Graphics& g)
{
    descriptorText.setColour(TextEditor::ColourIds::backgroundColourId, Colours::white);
    descriptorText.applyColourToAllText(Colours::black);
    
    dataText.setColour(TextEditor::ColourIds::backgroundColourId, Colours::white);
    dataText.applyColourToAllText(Colours::black);
}

void InfoSection::paintOverChildren (Graphics& g)
{
    //Line across the bottom
    g.drawLine(0, getHeight(), 200, getHeight(), 3);
    
    //Line down the middle
    g.drawLine(100, 0, 100, 50);
}

void InfoSection::resized()
{
    descriptorText.setBounds(0, 0, 100, getHeight());
    dataText.setBounds(100, 0, 100, getHeight());
}

void InfoSection::setData(String data)
{
    dataText.setText(data, dontSendNotification);
}

void InfoSection::clear()
{
    descriptorText.clear();
    dataText.clear();
}

void TextEditorLookAndFeel::drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& )
{
    
}
