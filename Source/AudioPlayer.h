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
    
    void loadNewFile(File* fileToLoad, int playPoint, int stopPoint, bool sendNotificationAtEnd);
    
    void stopPointReached();
    
    void pause();
    
    bool isPlaying() const;
    
    bool isPaused() const;
    
    void playFromPause();
    
    double getTransportPosition() const;
    
    void setGain(float gain);
    
    void setTransportPosition(double position);
    
    double getTransportLengthInSeconds() const;
    
    void stop();
    
private:
    AudioFormatManager formatManager;
    AudioFormatReader* reader;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    
    bool sendNotificationAtEndOfPlayback;
    int fileStopPoint;
    
    double pausePosition;
    
    //Have two readers and two reader sources and switch the transport between the two
};
