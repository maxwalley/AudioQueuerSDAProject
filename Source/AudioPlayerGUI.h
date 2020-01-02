/*
  ==============================================================================

    AudioPlayerGUI.h
    Created: 14 Nov 2019 3:04:38pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayPauseButton.h"
#include "PlayerControlButton.h"

//==============================================================================
/*
*/

class AudioPlayerGUI    : public Component
{
public:
    AudioPlayerGUI();
    ~AudioPlayerGUI();

    void paint (Graphics&) override;
    void resized() override;
    
    void audioStopped();
    void audioPaused();
    void audioPlayed();
    
    void changeTime(double audioPosition);
    
    Slider gainSlider;
    
    PlayPauseButton playButton;
    PlayerControlButton stopButton;
    PlayerControlButton nextButton;
    PlayerControlButton lastButton;
    
    /**Sets the play button to be enabled*/
    void setPlayButtonEnabled();
    
private:
    
    Label timeLabel;
    
    Label playingFileNameLabel;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerGUI)
};
