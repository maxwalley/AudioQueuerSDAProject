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
    
    void triggerButtonStateChange();
    
    Slider gainSlider;
    
    PlayPauseButton playButton;
    TextButton pauseButton;
    TextButton stopButton;
    TextButton openFileButton;
    
private:
    
    Label timeLabel;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerGUI)
};
