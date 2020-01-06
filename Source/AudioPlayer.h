/*
  ==============================================================================

    AudioPlayer.h
    Created: 6 Jan 2020 1:42:46pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class AudioPlayer   : public ActionBroadcaster
{
public:
    AudioPlayer();
    ~AudioPlayer();
    
    AudioTransportSource transport;
    
    void loadNewFile(File* fileToLoad);
    
    void stopPointReached();
    
private:
    AudioFormatManager formatManager;
    AudioFormatReader* reader;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    
    
    //Have two readers and two reader sources and switch the transport between the two
};
