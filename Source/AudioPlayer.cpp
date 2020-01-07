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

void AudioPlayer::loadNewFile(File* fileToLoad, int playPoint, int stopPoint, bool sendNotificationAtEnd)
{
    transport.stop();
    pausePosition = 0.0;
    
    //Resets the transport to nothing
    transport.setSource(nullptr);
    
    if(fileToLoad != nullptr)
    {
        reader = formatManager.createReaderFor(*fileToLoad);
    
        if(reader != nullptr)
        {
            std::unique_ptr<AudioFormatReaderSource> tempAudioFormatReaderSource (new AudioFormatReaderSource (reader, true));
    
            audioFormatReaderSource.reset(tempAudioFormatReaderSource.release());
        }
    
        transport.setSource(audioFormatReaderSource.get());
        transport.setPosition(playPoint);
        transport.start();
        
        fileStopPoint = stopPoint;
    }
    
    sendNotificationAtEndOfPlayback = sendNotificationAtEnd;
}

void AudioPlayer::stopPointReached()
{
    if(sendNotificationAtEndOfPlayback == true)
    {
        if((fileStopPoint != 0 && transport.getCurrentPosition() >= fileStopPoint) || transport.hasStreamFinished() == true)
        {
            sendActionMessage("Transport Finished");
        }
    }
}

void AudioPlayer::pause()
{
    pausePosition = transport.getCurrentPosition();
    transport.stop();
}

bool AudioPlayer::isPaused()
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
    transport.setPosition(pausePosition);
    transport.start();
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
