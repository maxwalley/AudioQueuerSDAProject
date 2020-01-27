/*
  ==============================================================================

    AudioPlayer.h
    Created: 6 Jan 2020 1:42:46pm
    Author:  Max Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

/**A class the holds an audio player. To start playing a file call loadNewFile(). If a file is paused call playFromPause() rather than loadNewFile().
 */

class AudioPlayer   : public AudioSource,
                      public ActionBroadcaster
{
public:
    /**Constructor */
    AudioPlayer();
    
    /**Destructor */
    ~AudioPlayer();
    
    /**Implementation of the AudioSource method*/
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    
    /**Implementation of the AudioSource method*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    /**Implementation of the AudioSource Method*/
    void releaseResources() override;
    
    /**Loads and plays a new file
     
     @param fileToLoad          the file to load and play. If this is nullptr no file will be loaded.
     @param playPoint           the point in the file to start playing from in seconds. If this is blank transport will start from the start of the file.
     @param stopPoint           the point in the file to stop playing at in seconds. If this is blank transport will end at the end of the file.
     @param sendNotificationAtEnd           whether to send a notification in the form of an ActionMessage at the end of playback. This message is "Transport Finished".
     */
    void loadNewFile(File* fileToLoad, int playPoint, int stopPoint, bool sendNotificationAtEnd);
    
    /**Pauses the transport
     
     @see playFromPause
     */
    void pause();
    
    /**Returns whether the player is currently playing or not
     
     @return whether the player is playing or not
     */
    bool isPlaying() const;
    
    /**Returns whether the player is currently paused or not
     
     @return whether the player is paused or not
     */
    bool isPaused() const;
    
    /**Plays the transport from a pause. If the transport is not paused this will do nothing*/
    void playFromPause();
    
    /**Returns the current position of the transport in seconds
     
     @return the current position of the transport in seconds
     */
    double getTransportPosition() const;
    
    /**Sets the gain of the player
     
     @param gain            the new gain multiplier to apply to audio processed by the player
     */
    void setGain(float gain);
    
    /**Sets the transport position at a new position in the current audio file being played
     
     @param position            the new position to move the transport to, in seconds
     */
    void setTransportPosition(double position);
    
    /**Returns the length of the current file loaded into the player in seconds
     
     @return the length of the current file loaded into the player in seconds
     */
    double getTransportLengthInSeconds() const;
    
    /**Stops the player playing*/
    void stop();
    
    /**Returns the AudioFormatManager this player is using
     
     @return the AudioFormatManager the player is using
     */
    AudioFormatManager* getAudioFormatManager();
    
private:
    AudioFormatManager formatManager;
    AudioFormatReader* reader;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    
    AudioTransportSource transport;
    
    bool sendNotificationAtEndOfPlayback;
    int fileStopPoint;
    
    double pausePosition;
    
    /**Sends action message "Transport Finished" when the transport finishes playing the current file it is playing */
    void stopPointReached();
};
