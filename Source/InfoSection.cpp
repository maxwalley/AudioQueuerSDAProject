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
InfoSection::InfoSection(String description, String data)
{
    setSize(200, 50);
    
    addAndMakeVisible(descriptorLabel);
    addAndMakeVisible(dataLabel);
    
    descriptorLabel.setJustificationType(Justification::centred);
    dataLabel.setJustificationType(Justification::centred);
    
    descriptorLabel.setText(description, dontSendNotification);
    dataLabel.setText(data, dontSendNotification);
}

InfoSection::~InfoSection()
{
}

void InfoSection::paint (Graphics& g)
{
    //Line across the bottom
    g.drawLine(0, 50, 200, 50);
    
    //Line down the middle
    g.drawLine(100, 0, 100, 50);
}

void InfoSection::resized()
{
    descriptorLabel.setBounds(0, 10, 100, 30);
    dataLabel.setBounds(100, 10, 100, 30);
}
