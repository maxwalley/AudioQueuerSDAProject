/*
  ==============================================================================

    AudioPlayer.cpp
    Created: 6 Jan 2020 1:42:46pm
    Author:  Max Walley

  ==============================================================================
*/

#include "AudioPlayer.h"

AudioPlayer::AudioPlayer()
{
    formatManager.registerBasicFormats();
}

AudioPlayer::~AudioPlayer()
{
    
}

void AudioPlayer::loadNewFile(File* fileToLoad)
{
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
    
        transport.start();
    }
}

void AudioPlayer::stopPointReached()
{
    if(transport.hasStreamFinished() == true)
    {
        sendActionMessage("Transport Finished");
    }
}
