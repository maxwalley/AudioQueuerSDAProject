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
    setSize(200, 50);
    
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

void InfoSection::paintOverChildren (Graphics& g)
{
    //Line across the bottom
    g.drawLine(0, 50, 200, 50, 3);
    
    //Line down the middle
    g.drawLine(100, 0, 100, 50);
}

void InfoSection::resized()
{
    descriptorText.setBounds(0, 0, 100, 50);
    dataText.setBounds(100, 0, 100, 50);
}

void InfoSection::setData(String data)
{
    dataText.setText(data, dontSendNotification);
}

void TextEditorLookAndFeel::drawTextEditorOutline(Graphics& g, int width, int height, TextEditor& )
{
    
}
