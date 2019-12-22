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

    void paint (Graphics&) override;
    void resized() override;
    
    TextButton openFileButton;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueControls)
};
