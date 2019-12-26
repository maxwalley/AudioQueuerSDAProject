/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "GUI/MenuModel.h"
#include "QueueTableModel.h"
#include "AudioWaveform.h"
#include "FFT.h"
#include "AudioPlayerGUI.h"
#include "InfoBox.h"
#include "Menu.h"

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
    void paintOverChildren(Graphics& g) override;
    void resized() override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    FileChooser fileChooser;
    File selectedFile;
    AudioFormatManager audioFormatManager;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    bool fileLoaded;
    
    ComboBox playTypeCombo;
    
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
    
    enum TransportState
    {
        playing,
        stopped,
        paused,
    };
    uint64_t pausePosition;
    
    TransportState transportState;
    
    AudioWaveform waveform;
    
    FFT transformImage;    
    AudioPlayerGUI playerGUI;
    
    QueueTableModel table;
    int selectedItem;
    
    void actionListenerCallback(const String& message) override;
    
    InfoBox infoBox;
    Menu menu;
    
    AudioDeviceManager deviceManager;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
