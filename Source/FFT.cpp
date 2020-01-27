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
FFT::FFT() : transform(fftOrder), inputIndex(0), arrayPushingFinished(false), spectogram(Image::RGB, 512, 512, true)
{
    setSize(256, 256);
    
    Timer::startTimer(40);
}

FFT::~FFT()
{
}

void FFT::paint (Graphics& g)
{
    g.drawImage(spectogram, 0, 0, 256, 256, 0, 0, 512, 512);
}

void FFT::fillInputArray(float sample)
{
    //Checks the input array has enough data for the fft
    if(transformInputArray.size() == fftSize)
    {
        //If the output array needs to be refilled
        if(arrayPushingFinished == false)
        {
            //Clears the output array and fills it with the input array
            transformOutputArray.clear();
            transformOutputArray.addArray(transformInputArray);
            arrayPushingFinished = true;
        }
        transformInputArray.clear();
    }
    //Puts the latest sample into the input array
    transformInputArray.add(sample);
}

void FFT::drawSpectogram()
{
    //Array of double the size of the output array
    float array[fftSize * 2];
    
    //Fills first half of new array with the data of the output array
    for(int index = 0; index < fftSize; index++)
    {
        array[index] = transformOutputArray.getReference(index);
    }
    
    auto rightHandEdge = spectogram.getWidth() - 1;
    auto imageHeight   = spectogram.getHeight();
    
    //Moves the specogram image one pixel to the left
    spectogram.moveImageSection (0, 0, 1, 0, rightHandEdge - 1, imageHeight);
    
    //Performs the transform using the new array as input and output
    transform.performRealOnlyForwardTransform(array);

    //Finds the range of values produced by the transform
    auto maxLevel = FloatVectorOperations::findMinAndMax (array, fftSize/2);
    
    //Iterates through the vertical pixels of the spectogram image working out and setting their value based on the fft
    for (auto y = 1; y < imageHeight; ++y)
    {
        auto skewedProportionY = 1.0f - std::exp (std::log (y / (float) imageHeight) * 0.2f);
        
        auto fftDataIndex = jlimit (0, fftSize / 2, (int) (skewedProportionY * fftSize / 2));
        auto level = jmap (array[fftDataIndex], 0.0f, jmax (maxLevel.getEnd(), 1e-5f), 0.0f, 1.0f);
        
        spectogram.setPixelAt (rightHandEdge - 1, y, Colour::fromHSV (level, 1.0f, level, 1.0f));
    }
    

}

void FFT::timerCallback()
{
    //Checks a new sample is ready to be processed
    if (arrayPushingFinished == true)
    {
        //Draws spectogram image with new sample
        drawSpectogram();
        
        //Resets this to ask for a new sample
        arrayPushingFinished = false;
        
        //Repaints entire component
        repaint();
    }
}
