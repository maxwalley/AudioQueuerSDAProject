/*
  ==============================================================================

    AudioPlayerGUI.h
    Created: 14 Nov 2019 3:04:38pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayerGUIButton.h"

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
    
    PlayerGUIButton playPauseButton;
    PlayerGUIButton stopButton;
    PlayerGUIButton nextButton;
    PlayerGUIButton lastButton;
    
    void setButtonEnabled(Button* button, bool enabled);
    
private:
    
    Label timeLabel;
    
    Label playingFileNameLabel;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerGUI)
};
