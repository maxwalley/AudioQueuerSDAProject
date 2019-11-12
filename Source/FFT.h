/*
  ==============================================================================

    FFT.h
    Created: 7 Nov 2019 2:26:28pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Array.hpp"

//==============================================================================
/*
*/
class FFT    : public Component
{
public:
    FFT();
    ~FFT();

    void paint (Graphics&) override;
    void resized() override;

private:
    int order;
    
    dsp::FFT transform;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFT)
};
