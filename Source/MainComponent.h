/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioPlayer.h"
#include "WAVWriter.h"
#include "GUI/MenuModel.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent
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
    AudioPlayer audioPlayer;
    WAVWriter wavWriter;
    
    MenuModel menuSettings;
    MenuBarComponent menu;
    
    AudioDeviceManager deviceManager;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
