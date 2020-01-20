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
    /**Constructor*/
    AudioPlayerGUI();
    
    /**Destructor*/
    ~AudioPlayerGUI();

    /**Implementation of the Component method*/
    void paint (Graphics&) override;
    
    /**Implementation of the Component method*/
    void resized() override;
    
    /**Changes components of this class to show a state where audio is stopped*/
    void audioStopped();
    
    /**Changes components of this class to show a state where audio is paused*/
    void audioPaused();
    
    /**Changes components of this class to show a state where audio is playing*/
    void audioPlayed();
    
    /**Changes the time shown by the time label
     
     @param audioPosition           current audio position in seconds
     */
    void changeTime(double audioPosition);
    
    Slider gainSlider;
    
    PlayerGUIButton playPauseButton;
    PlayerGUIButton stopButton;
    PlayerGUIButton nextButton;
    PlayerGUIButton lastButton;
    
    /**Changes whether a button on the component is enabled
     
     @param button          the button to change whether its enabled
     @param enabled         whether its enabled
     */
    void setButtonEnabled(Button* button, bool enabled);
    
private:
    
    Label timeLabel;
    
    Label playingFileNameLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayerGUI)
};
