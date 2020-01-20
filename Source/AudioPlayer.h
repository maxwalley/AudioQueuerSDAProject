/*
  ==============================================================================

    AudioPlayer.h
    Created: 6 Jan 2020 1:42:46pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

class AudioPlayer   : public AudioSource,
                      public ActionBroadcaster
{
public:
    /** Constructor */
    AudioPlayer();
    
    /** Destructor */
    ~AudioPlayer();
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    void releaseResources() override;
    
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
    
    AudioFormatManager* getAudioFormatManager();
    
private:
    AudioFormatManager formatManager;
    AudioFormatReader* reader;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    
    AudioTransportSource transport;
    
    bool sendNotificationAtEndOfPlayback;
    int fileStopPoint;
    
    double pausePosition;
};
