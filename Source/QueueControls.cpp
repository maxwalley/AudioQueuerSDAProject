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
    
    addAndMakeVisible(loopQueueButton);
    loopQueueButton.setToggleState(false, dontSendNotification);
    
    addAndMakeVisible(loopQueueLabel);
    loopQueueLabel.setText("Loop Queue?", dontSendNotification);
}

QueueControls::~QueueControls()
{
    
}

void QueueControls::resized()
{
    openFileButton.setBounds(0, 0, getWidth(), 30);
    
    loopQueueButton.setBounds(75, 50, 25, 25);
    loopQueueLabel.setBounds(0, 50, 75, 25);
}

bool QueueControls::getLoopQueueButtonState()
{
    return loopQueueButton.getToggleState();
}
