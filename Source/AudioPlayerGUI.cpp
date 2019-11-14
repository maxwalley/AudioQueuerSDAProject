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
AudioPlayerGUI::AudioPlayerGUI() : playButton("Play"), pauseButton("Pause"), stopButton("Stop"), openFileButton("Open File")
{
    setSize(200, 150);
    
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearVertical);
    gainSlider.setRange(0, 1);
    gainSlider.setValue(0.5);
       
    addAndMakeVisible(playButton);
    playButton.setClickingTogglesState(true);
    playButton.setToggleState(false, dontSendNotification);
       
    addAndMakeVisible(pauseButton);
    pauseButton.setClickingTogglesState(true);
    pauseButton.setToggleState(false, dontSendNotification);
       
    addAndMakeVisible(stopButton);
    stopButton.setClickingTogglesState(true);
    stopButton.setToggleState(true, dontSendNotification);
       
    addAndMakeVisible(openFileButton);

    addAndMakeVisible(timeLabel);
    timeLabel.setText("0", dontSendNotification);
}

AudioPlayerGUI::~AudioPlayerGUI()
{
}

void AudioPlayerGUI::paint (Graphics& g)
{
    playButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
    pauseButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
    stopButton.setColour(TextButton::ColourIds::buttonOnColourId, Colours::darkred);
}

void AudioPlayerGUI::resized()
{
    gainSlider.setBounds(170, 0, 30, 150);
    openFileButton.setBounds(0, 0, 150, 50);
    playButton.setBounds(0, 50, 50, 50);
    pauseButton.setBounds(50, 50, 50, 50);
    stopButton.setBounds(100, 50, 50, 50);
    timeLabel.setBounds(0, 110, 150, 40);
}

void AudioPlayerGUI::audioStopped()
{
    stopButton.setEnabled(false);
    pauseButton.setToggleState(false, dontSendNotification);
    pauseButton.setEnabled(false);
    playButton.setToggleState(false, dontSendNotification);
    playButton.setEnabled(true);
}

void AudioPlayerGUI::audioPaused()
{
    pauseButton.setEnabled(false);
    playButton.setToggleState(false, dontSendNotification);
    playButton.setEnabled(true);
    stopButton.setToggleState(false, dontSendNotification);
    stopButton.setEnabled(true);
}

void AudioPlayerGUI::audioPlayed()
{
    playButton.setEnabled(false);
    stopButton.setToggleState(false, dontSendNotification);
    stopButton.setEnabled(true);
    pauseButton.setToggleState(false, dontSendNotification);
    pauseButton.setEnabled(true);
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
