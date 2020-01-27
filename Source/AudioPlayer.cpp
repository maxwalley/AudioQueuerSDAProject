/*
  ==============================================================================

    AudioPlayer.cpp
    Created: 6 Jan 2020 1:42:46pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioPlayer.h"

AudioPlayer::AudioPlayer() : sendNotificationAtEndOfPlayback(true), fileStopPoint(0), pausePosition(0.0)
{
    formatManager.registerBasicFormats();
}

AudioPlayer::~AudioPlayer()
{
    
}

void AudioPlayer::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transport.prepareToPlay(samplesPerBlockExpected, sampleRate);
}

void AudioPlayer::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    if(transport.isPlaying() == true)
    {
        transport.getNextAudioBlock(bufferToFill);
    }
    
    //Checks if a stop point has been reached
    stopPointReached();
}

void AudioPlayer::releaseResources()
{
    transport.releaseResources();
}

void AudioPlayer::loadNewFile(File* fileToLoad, int playPoint, int stopPoint, bool sendNotificationAtEnd)
{
    //resets the transport
    stop();
    
    //Checks the new file is a valid file
    if(fileToLoad != nullptr)
    {
        reader = formatManager.createReaderFor(*fileToLoad);
    
        //Checks the manager successfully created a reader for the file
        if(reader != nullptr)
        {
            //Creates a temp audioFormatReaderSource and sets it to the reader
            std::unique_ptr<AudioFormatReaderSource> tempAudioFormatReaderSource (new AudioFormatReaderSource (reader, true));
    
            //Sets main audioFormatReaderSource to the temp one and wipes the temp one
            audioFormatReaderSource.reset(tempAudioFormatReaderSource.release());
        }
    
        //Sets the transport source to the main AudioFormatReaderSource
        transport.setSource(audioFormatReaderSource.get(), 0, nullptr, reader->sampleRate, reader->numChannels);
        
        //Sets start position to the playpoint. (If there is no play point this will be 0)
        transport.setPosition(playPoint);
        
        //Starts the transport
        transport.start();
        
        fileStopPoint = stopPoint;
    }
    
    sendNotificationAtEndOfPlayback = sendNotificationAtEnd;
}

void AudioPlayer::stopPointReached()
{
    //Checks that its meant to send a notification when playback ends
    if(sendNotificationAtEndOfPlayback == true)
    {
        //Checks if the stop point is not 0 then has transport hit it OR has the transport finished the file it was playing
        if((fileStopPoint != 0 && transport.getCurrentPosition() >= fileStopPoint) || transport.hasStreamFinished() == true)
        {
            sendActionMessage("Transport Finished");
        }
    }
}

void AudioPlayer::pause()
{
    //Keeps track of where the transport was paused
    pausePosition = transport.getCurrentPosition();
    transport.stop();
}

bool AudioPlayer::isPlaying() const
{
    return transport.isPlaying();
}

bool AudioPlayer::isPaused() const
{
    if(pausePosition == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void AudioPlayer::playFromPause()
{
    //Checks pause is enabled
    if(isPaused() == true)
    {
        //Sets the transport position to the held pause position and restarts it
        transport.setPosition(pausePosition);
        transport.start();
    }
}

double AudioPlayer::getTransportPosition() const
{
    return transport.getCurrentPosition();
}

void AudioPlayer::setGain(float gain)
{
    transport.setGain(gain);
}

void AudioPlayer::setTransportPosition(double position)
{
    transport.setPosition(position);
}

double AudioPlayer::getTransportLengthInSeconds() const
{
    return transport.getLengthInSeconds();
}

void AudioPlayer::stop()
{
    //Stops the transport and resets pause position
    transport.stop();
    pausePosition = 0;
    
    //Sets the transport as having no source
    transport.setSource(nullptr);
}

AudioFormatManager* AudioPlayer::getAudioFormatManager()
{
    return &formatManager;
}
