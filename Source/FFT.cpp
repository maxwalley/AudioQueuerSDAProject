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
    if(transformInputArray.size() == fftSize)
    {
        if(arrayPushingFinished == false)
        {
            transformOutputArray.clear();
            transformOutputArray.addArray(transformInputArray);
            arrayPushingFinished = true;
        }
        transformInputArray.clear();
    }
    transformInputArray.add(sample);
}

void FFT::drawSpectogram()
{
    spectogram.moveImageSection (0, 0, 1, 0, spectogram.getWidth() - 1, spectogram.getHeight());
    
    float array[fftSize * 2];
    
    for(int index = 0; index < fftSize; index++)
    {
        array[index] = transformOutputArray.getReference(index);
    }
    
    auto rightHandEdge = spectogram.getWidth() - 1;
    auto imageHeight   = spectogram.getHeight();
    
    spectogram.moveImageSection (0, 0, 1, 0, rightHandEdge - 1, imageHeight);
    
    transform.performRealOnlyForwardTransform(array);

    auto maxLevel = FloatVectorOperations::findMinAndMax (array, fftSize/2);
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
    if (arrayPushingFinished == true)
    {
        drawSpectogram();
        arrayPushingFinished = false;
        repaint();
    }
}

void FFT::timerTrigger()
{
    Timer::startTimer(40);
}
