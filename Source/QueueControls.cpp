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
    setSize(150, 300);
    
    addAndMakeVisible(openFileButton);
    
    addAndMakeVisible(loopQueueButton);
    loopQueueButton.setToggleState(false, dontSendNotification);
    
    addAndMakeVisible(loopQueueLabel);
    loopQueueLabel.setText("Loop Queue?", dontSendNotification);
    
    addAndMakeVisible(shuffleQueueButton);
    shuffleQueueButton.setToggleState(false, dontSendNotification);
    
    addAndMakeVisible(shuffleQueueLabel);
    shuffleQueueLabel.setText("Shuffle Queue?", dontSendNotification);
    
    addAndMakeVisible(playContinuouslyButton);
    playContinuouslyButton.setToggleState(true, dontSendNotification);
    
    addAndMakeVisible(playContinuouslyLabel);
    playContinuouslyLabel.setText("Play Continuously?", dontSendNotification);
}

QueueControls::~QueueControls()
{
    
}

void QueueControls::paint(Graphics& g)
{
    openFileButton.setColour(TextButton::ColourIds::buttonColourId, Colours::white);
    openFileButton.setColour(TextButton::ColourIds::textColourOffId, Colours::black);
    openFileButton.setColour(TextButton::ColourIds::textColourOnId, Colours::black);
}

void QueueControls::resized()
{
    openFileButton.setBounds(0, 0, getWidth(), 30);
    
    loopQueueButton.setBounds(125, 50, 25, 25);
    loopQueueLabel.setBounds(0, 50, 125, 25);
    
    shuffleQueueButton.setBounds(125, 100, 25, 25);
    shuffleQueueLabel.setBounds(0, 100, 125, 25);
    
    playContinuouslyButton.setBounds(125, 150, 25, 25);
    playContinuouslyLabel.setBounds(0, 150, 125, 25);
}

bool QueueControls::getLoopQueueButtonState()
{
    return loopQueueButton.getToggleState();
}

bool QueueControls::getShuffleQueueButtonState()
{
    return shuffleQueueButton.getToggleState();
}

bool QueueControls::getContinuousButtonState()
{
    return playContinuouslyButton.getToggleState();
}

void QueueControls::changeToggleState(int control)
{
    //if control is the loop button
    if(control == loopQueue)
    {
        if(loopQueueButton.getToggleState() == true)
        {
            loopQueueButton.setToggleState(false, dontSendNotification);
        }
        else if(loopQueueButton.getToggleState() == false)
        {
            loopQueueButton.setToggleState(true, dontSendNotification);
        }
    }
    
    //if control is the shuffle control
    else if(control == shuffleQueue)
    {
        if(shuffleQueueButton.getToggleState() == true)
        {
            shuffleQueueButton.setToggleState(false, dontSendNotification);
        }
        else if (shuffleQueueButton.getToggleState() == false)
        {
            shuffleQueueButton.setToggleState(true, dontSendNotification);
        }
    }
    
    //if control is the play continuous control
    else if(control == playContinuously)
    {
        if(playContinuouslyButton.getToggleState() == true)
        {
            playContinuouslyButton.setToggleState(false, dontSendNotification);
        }
        else if(playContinuouslyButton.getToggleState() == false)
        {
            playContinuouslyButton.setToggleState(true, dontSendNotification);
        }
    }
}
