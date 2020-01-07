/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioTable.h"
#include "AudioWaveform.h"
#include "FFT.h"
#include "AudioPlayerGUI.h"
#include "InfoBox.h"
#include "Menu.h"
#include "AudioPlayer.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener,
                        public Slider::Listener,
                        public Timer,
                        public ActionListener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    FileChooser fileChooser;
    File selectedFile;
    AudioFormatManager audioFormatManager;
    bool fileLoaded;
    
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    
    /**Adds a file to the queue*/
    void addFile();
    
    /**Plays the queue*/
    void playQueue();
    
    /**Pauses the audio*/
    void pauseAudio();
    
    /**Stops the audio*/
    void stopAudio();
    
    void timerCallback() override;
    int timerCount;
    
    void mouseDown (const MouseEvent &event) override;
    void changeAudioPosition(int xAxis);
    
    AudioWaveform waveform;
    
    FFT transformImage;    
    AudioPlayerGUI playerGUI;
    
    AudioTable table;
    
    void actionListenerCallback(const String& message) override;
    
    void setUpPlayer();
    
    InfoBox infoBox;
    Menu menu;
    
    AudioPlayer player;
    
    AudioDeviceManager deviceManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
