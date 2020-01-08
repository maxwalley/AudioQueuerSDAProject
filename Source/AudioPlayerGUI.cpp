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
AudioPlayerGUI::AudioPlayerGUI() 
{
    setSize(200, 250);
    
    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    gainSlider.setTextBoxStyle(Slider::NoTextBox, true, 0, 0);
    gainSlider.setRange(0, 1);
    gainSlider.setValue(0.5);
       
    /*addAndMakeVisible(playButton);
    playButton.setEnabled(false);*/
    
    stopButtonPath.addRectangle(stopButton.getWidth()/3, stopButton.getHeight()/3, stopButton.getWidth()/3, stopButton.getHeight()/3);
    stopButton.setButtonImage(stopButtonPath);
    
    nextButtonPath.startNewSubPath((nextButton.getWidth()/3) * 2, nextButton.getHeight()/3);
    nextButtonPath.lineTo((nextButton.getWidth()/3) * 2, (nextButton.getHeight()/3) * 2);
    nextButtonPath.addTriangle(nextButton.getWidth()/3, getHeight()/3, (getWidth()/3) * 2, getHeight()/2, getWidth()/3, (getHeight()/3) * 2);
    nextButton.setButtonImage(nextButtonPath);
    
    lastButtonPath.startNewSubPath(lastButton.getWidth()/3, lastButton.getHeight()/3);
    lastButtonPath.lineTo(lastButton.getWidth()/3, (lastButton.getHeight()/3) * 2);
    lastButtonPath.addTriangle(lastButton.getWidth()/3, lastButton.getHeight()/2, (lastButton.getWidth()/3) * 2, lastButton.getHeight()/3, (lastButton.getWidth()/3) * 2, (lastButton.getHeight()/3) * 2);
    lastButton.setButtonImage(lastButtonPath);
       
    addAndMakeVisible(nextButton);
    
    addAndMakeVisible(lastButton);
    
    addAndMakeVisible(stopButton);
    
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
    
    //playButton.setBounds(75, 80, 50, 50);
    stopButton.setBounds(80, 140, 40, 40);
    nextButton.setBounds(165, 85, 35, 35);
    lastButton.setBounds(0, 85, 35, 35);
    
    gainSlider.setBounds(0, 200, getWidth(), 20);
}

void AudioPlayerGUI::audioStopped()
{
    //playButton.changeState(0);
    timeLabel.setText("", dontSendNotification);
}

void AudioPlayerGUI::audioPaused()
{
    //playButton.changeState(0);
}

void AudioPlayerGUI::audioPlayed()
{
    stopButton.setToggleState(false, dontSendNotification);
    //playButton.changeState(1);
    
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

void AudioPlayerGUI::setPlayButtonEnabled()
{
    //playButton.setEnabled(true);
}
