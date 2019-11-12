/*
  ==============================================================================

    AudioPlayer.h
    Created: 3 Nov 2019 1:00:25pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioWaveform.h"

//==============================================================================
/*
*/
class AudioPlayer    : public Component,
                       public AudioSource,
                       public Button::Listener,
                       public Slider::Listener,
                       public Timer
{
public:
    AudioPlayer();
    ~AudioPlayer();

    void paint (Graphics&) override;
    void paintOverChildren(Graphics& g) override;
    void resized() override;
    
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    
    AudioFormatManager getFormatManager() const;

private:
    FileChooser fileChooser;
    File selectedFile;
    AudioFormatManager audioFormatManager;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    AudioTransportSource audioTransportSource;
    bool fileLoaded;
    
    Label timeLabel;
    Slider gainSlider;
    TextButton playButton;
    TextButton pauseButton;
    TextButton stopButton;
    TextButton openFileButton;
    
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
    
    enum
    {
        fftOrder = 10,
        fftSize = 1 << fftOrder,
    };
    
    dsp::FFT transform;
    Array<float> transformInputArray;
    Array<float> transformOutputArray;
    int inputIndex;
    //float transformInputArray[1024];
    //float transformOutputArray[2048];
    bool arrayPushingFinished;
    void fillInputArray(float sample);
    void drawSpectogram();
    
    Image spectogram;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPlayer)
};
