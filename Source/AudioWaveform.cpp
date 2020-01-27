/*
  ==============================================================================

    AudioWaveform.cpp
    Created: 6 Nov 2019 8:40:23pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioWaveform.h"

//==============================================================================
AudioWaveform::AudioWaveform(AudioFormatManager &formatManagerToUse) : thumbnail(512, formatManagerToUse, thumbnailCache), thumbnailCache(5), transportXPos(0)
{
    backgroundColour = Colours::white;
    waveformColour = Colours::black;
}

AudioWaveform::~AudioWaveform()
{
}

void AudioWaveform::paint (Graphics& g)
{
    //Draws background area
    g.setColour(backgroundColour);
    g.fillRect(0, 0, getWidth(), getHeight());
    
    //Draws the channels in the waveform
    g.setColour(waveformColour);
    thumbnail.drawChannels(g, Rectangle<int>(getWidth(), getHeight()), 0, thumbnail.getTotalLength(), 1.0);
    
    //Checks if the transport position along is zero
    if(transportXPos != 0)
    {
        //Draws a line representing the transport position on the waveform
        g.setColour(Colours::black);
        g.drawLine(transportXPos, 0, transportXPos, 150);
    }
}

void AudioWaveform::set(InputSource *newSource)
{
    thumbnail.clear();
    thumbnail.setSource(newSource);
    
    //Loops until the thumbnail is fully loaded and then repaints the entire component
    while (thumbnail.isFullyLoaded() == false)
    {
    }
    repaint();
}

double AudioWaveform::getThumbnailLength() const
{
    return thumbnail.getTotalLength();
}

void AudioWaveform::clear()
{
    //Resets the transport position on the waveform
    transportXPos = 0;
    
    thumbnail.clear();
    repaint();
}

void AudioWaveform::moveTransportLine(double xPixelToMoveTo)
{
    transportXPos = xPixelToMoveTo;
    repaint();
}

void AudioWaveform::setBackgroundColour(Colour newColour)
{
    backgroundColour = newColour;
    repaint();
}

void AudioWaveform::setWaveformColour(Colour newColour)
{
    waveformColour = newColour;
    repaint();
}
