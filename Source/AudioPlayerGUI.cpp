/*
  ==============================================================================

    AudioPlayerGUI.cpp
    Created: 14 Nov 2019 3:04:38pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayerGUI.h"

//==============================================================================
AudioPlayerGUI::AudioPlayerGUI()  : playPauseButton(PlayerGUIButton::play), stopButton(PlayerGUIButton::stop), nextButton(PlayerGUIButton::next), lastButton(PlayerGUIButton::last)
{
    setSize(200, 250);
    
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    gainSlider.setRange(0, 1);
    gainSlider.setValue(0.5);
    
    addAndMakeVisible(playPauseButton);
    addAndMakeVisible(stopButton);
    addAndMakeVisible(nextButton);
    addAndMakeVisible(lastButton);
    
    addAndMakeVisible(timeLabel);
    timeLabel.setText("", dontSendNotification);
    
    addAndMakeVisible(playingFileNameLabel);
}

AudioPlayerGUI::~AudioPlayerGUI()
{
}

void AudioPlayerGUI::paint (Graphics& g)
{
    gainSlider.setColour(Slider::ColourIds::backgroundColourId, Colours::black);
    gainSlider.setColour(Slider::ColourIds::thumbColourId, Colours::white);
}

void AudioPlayerGUI::resized()
{
    timeLabel.setBounds(0, 0, 50, 30);
    
    playPauseButton.setBounds(75, 80, 50, 50);
    stopButton.setBounds(80, 140, 40, 40);
    nextButton.setBounds(165, 85, 35, 35);
    lastButton.setBounds(0, 85, 35, 35);
    
    gainSlider.setBounds(0, 200, getWidth(), 20);
}

void AudioPlayerGUI::audioStopped()
{
    playPauseButton.changeFunction(PlayerGUIButton::play);
    timeLabel.setText("", dontSendNotification);
}

void AudioPlayerGUI::audioPaused()
{
    playPauseButton.changeFunction(PlayerGUIButton::play);
}

void AudioPlayerGUI::audioPlayed()
{
    stopButton.setToggleState(false, dontSendNotification);
    playPauseButton.changeFunction(PlayerGUIButton::pause);
    
}

void AudioPlayerGUI::changeTime(double audioPosition)
{
    int64_t numMins = floor(audioPosition / 60);
    double numSecs = fmod(audioPosition, 60);
    double decPoint = fmod(numSecs, 1);
    int64_t numSecsInt = numSecs - decPoint;
    
    std::string numMinsString = std::to_string(numMins);
    std::string numSecsString = std::to_string(numSecsInt);
    
    std::string fullTime = numMinsString + ":" + numSecsString;
        
    const MessageManagerLock labelLock;
    timeLabel.setText(fullTime, dontSendNotification);
}

void AudioPlayerGUI::setButtonEnabled(Button* button, bool enabled)
{
    button->setEnabled(enabled);
}
