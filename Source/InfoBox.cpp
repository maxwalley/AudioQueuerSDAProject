/*
  ==============================================================================

    InfoBox.cpp
    Created: 14 Dec 2019 7:42:31pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "InfoBox.h"

//==============================================================================
InfoBox::InfoBox()
{
    setSize(200, 500);
}

InfoBox::~InfoBox()
{
}

void InfoBox::paint (Graphics& g)
{
    g.drawRoundedRectangle(0, 0, 200, 500, 10, 4);
}

void InfoBox::resized()
{
    
}
