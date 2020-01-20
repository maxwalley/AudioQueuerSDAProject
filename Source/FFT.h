/*
  ==============================================================================

    FFT.h
    Created: 7 Nov 2019 2:26:28pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FFT    : public Component,
               public Timer
{
public:
    /**Constructor*/
    FFT();
    
    /**Destructor*/
    ~FFT();

    /**Implementation of the Component method*/
    void paint (Graphics&) override;
    
    /**Inputs data into the FFT
     
     @param sample          the input sample to put into the FFT
     */
    void fillInputArray(float sample);
    
    /**Triggers the timer to start which starts drawing the FFT*/
    void timerTrigger();
    
private:
    dsp::FFT transform;
    Array<float> transformInputArray;
    Array<float> transformOutputArray;
    int inputIndex;
    bool arrayPushingFinished;
    
    /**Draws the spectogram image*/
    void drawSpectogram();
    
    enum
    {
        fftOrder = 10,
        fftSize = 1 << fftOrder,
    };
    
    Image spectogram;
    
    /**Implementation of the Timer method*/
    void timerCallback() override;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FFT)
};
