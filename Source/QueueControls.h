/*
  ==============================================================================

    QueueControls.h
    Created: 22 Dec 2019 6:41:33pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class QueueControls    : public Component
{
public:
    QueueControls();
    ~QueueControls();

    void paint(Graphics& g) override;
    void resized() override;
    
    TextButton openFileButton;
    
    /**Returns the state of the loop queue toggle button
     true for button selected
     false for button deselected*/
    bool getLoopQueueButtonState();

    /**Returns the state of the shuffle queue toggle button
     true for button selected
     false for button deselected*/
    bool getShuffleQueueButtonState();
    
private:
    ToggleButton loopQueueButton;
    Label loopQueueLabel;
    
    ToggleButton shuffleQueueButton;
    Label shuffleQueueLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueControls)
};
