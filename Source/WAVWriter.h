/*
  ==============================================================================

    WAVWriter.h
    Created: 11 Nov 2019 5:30:39pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class WAVWriter    : public Component,
                     public Button::Listener
{
public:
    WAVWriter(int sampleRate, int numChannels, int bitDepth);
    ~WAVWriter();

    void paint (Graphics&) override;
    void resized() override;

private:
    //WavAudioFormat wav;
    //FileOutputStream fileStream;
    
    TextButton splitFileButton;
    void buttonClicked(Button* button) override;
    
    FileChooser filePicker;
    File chosenDirectory;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WAVWriter)
};
