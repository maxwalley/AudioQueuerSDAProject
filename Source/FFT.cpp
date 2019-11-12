/*
  ==============================================================================

    FFT.cpp
    Created: 7 Nov 2019 2:26:28pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "FFT.h"

//==============================================================================
FFT::FFT() : order(10), transform(order)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

FFT::~FFT()
{
}

void FFT::paint (Graphics& g)
{
    
}

void FFT::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
