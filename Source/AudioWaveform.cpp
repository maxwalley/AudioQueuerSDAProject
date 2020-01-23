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
AudioWaveform::AudioWaveform(AudioFormatManager &formatManagerToUse) : thumbnail(512, formatManagerToUse, thumbnailCache), thumbnailArea(0, 0, 200, 150), thumbnailCache(5), transportXPos(0)
{
    setAlwaysOnTop(true);
    
    backgroundColour = Colours::white;
    waveformColour = Colours::black;
}

AudioWaveform::~AudioWaveform()
{
}

void AudioWaveform::paint (Graphics& g)
{
    g.setColour(backgroundColour);
    g.fillRect(thumbnailArea);
    g.setColour(waveformColour);
    thumbnail.drawChannels(g, thumbnailArea, 0, thumbnail.getTotalLength(), 1.0);
    
    if(transportXPos != 0)
    {
        g.setColour(Colours::black);
        g.drawLine(transportXPos, 0, transportXPos, 150);
    }
}

void AudioWaveform::set(InputSource *newSource)
{
    thumbnail.clear();
    thumbnail.setSource(newSource);
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
