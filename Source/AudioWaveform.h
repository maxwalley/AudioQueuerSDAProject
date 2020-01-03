/*
  ==============================================================================

    AudioWaveform.h
    Created: 6 Nov 2019 8:40:23pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AudioWaveform    : public Component
{
public:
    AudioWaveform(AudioFormatManager &formatManagerToUse);
    ~AudioWaveform();
    
    void paint (Graphics&) override;
    
    void set(InputSource *newSource);
    
    double getThumbnailLength() const;
    
    /**Clears the waveform*/
    void clear();
    
private:
    AudioThumbnail thumbnail;
    Rectangle<int> thumbnailArea;
    AudioThumbnailCache thumbnailCache;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioWaveform)
};
