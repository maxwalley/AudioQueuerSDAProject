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
/** A component class for displaying an audio waveform. Set the file for it to show using the set() method.
*/
class AudioWaveform    : public Component
{
public:
    AudioWaveform(AudioFormatManager &formatManagerToUse);
    ~AudioWaveform();
    
    /**Implementation of the Component method*/
    void paint (Graphics&) override;
    
    /**Sets the waveform to show a source
     
     @param newSource           the source to show
     */
    void set(InputSource* newSource);
    
    /**Returns the length of the file the thumbnail is showing in seconds
     
     @return the length of the file the thumbnail is showing
     */
    double getThumbnailLength() const;
    
    /**Clears the waveform*/
    void clear();
    
    /**Moves the transport line to a new position on the waveform
     
     @param xPixelToMoveTo          the new position on the waveform to move to in pixels
     */
    void moveTransportLine(double xPixelToMoveTo);
    
private:
    AudioThumbnail thumbnail;
    Rectangle<int> thumbnailArea;
    AudioThumbnailCache thumbnailCache;
    
    int transportXPos;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioWaveform)
};
