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
AudioWaveform::AudioWaveform(AudioFormatManager &formatManagerToUse) : thumbnail(512, formatManagerToUse, thumbnailCache), thumbnailArea(0, 0, 200, 150), thumbnailCache(5)
{
    setSize(200, 150);
}

AudioWaveform::~AudioWaveform()
{
}

void AudioWaveform::paint (Graphics& g)
{
    g.setColour(Colours::white);
    g.fillRect(thumbnailArea);
    g.setColour(Colours::black);
    thumbnail.drawChannels(g, thumbnailArea, 0, thumbnail.getTotalLength(), 1.0);
}

void AudioWaveform::resized()
{

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

double AudioWaveform::getThumbnailLenght() const
{
    return thumbnail.getTotalLength();
}
