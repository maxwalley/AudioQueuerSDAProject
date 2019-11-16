/*
  ==============================================================================

    QueueFooter.h
    Created: 16 Nov 2019 7:58:26pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class QueueFooter    : public Component
{
public:
    QueueFooter();
    ~QueueFooter();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueFooter)
};
