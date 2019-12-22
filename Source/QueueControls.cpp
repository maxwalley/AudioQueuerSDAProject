/*
  ==============================================================================

    QueueControls.cpp
    Created: 22 Dec 2019 6:41:33pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueControls.h"

//==============================================================================
QueueControls::QueueControls() : openFileButton("Open File")
{
    setSize(100, 300);
    
    addAndMakeVisible(openFileButton);
}

QueueControls::~QueueControls()
{
}

void QueueControls::paint (Graphics& g)
{
    
}

void QueueControls::resized()
{
    openFileButton.setBounds(0, 0, getWidth(), 30);
}
