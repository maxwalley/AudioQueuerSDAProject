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
    
        transport.setSource(audioFormatReaderSource.get(), 0, nullptr, reader->sampleRate, reader->numChannels);
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

double AudioPlayer::getTransportLengthInSeconds() const
{
    return transport.getLengthInSeconds();
}

void AudioPlayer::stop()
{
    transport.stop();
    pausePosition = 0;
    transport.setSource(nullptr);
}
