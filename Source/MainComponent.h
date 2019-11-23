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

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public MenuBarModel,
                        public Button::Listener,
                        public Slider::Listener,
                        public Timer
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
    
    //==============================================================================
    StringArray getMenuBarNames() override;
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
private:
    //==============================================================================
    // Your private member variables go here...
    FileChooser fileChooser;
    File selectedFile;
    AudioFormatManager audioFormatManager;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    AudioTransportSource audioTransportSource;
    bool fileLoaded;
    
    /*Label timeLabel;
    Slider gainSlider;
    TextButton playButton;
    TextButton pauseButton;
    TextButton stopButton;
    TextButton openFileButton;*/
    
    void buttonClicked(Button* button) override;
    void sliderValueChanged(Slider* slider) override;
    
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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
