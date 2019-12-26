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

    void resized() override;
    
    TextButton openFileButton;
    
    /**Returns the state of the loop queue toggle button
     true for button selected
     false for button deselected*/
    bool getLoopQueueButtonState();

private:
    ToggleButton loopQueueButton;
    Label loopQueueLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueControls)
};
