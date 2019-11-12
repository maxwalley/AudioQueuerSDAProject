/*
  ==============================================================================

    WAVWriter.cpp
    Created: 11 Nov 2019 5:30:39pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "WAVWriter.h"

//==============================================================================
WAVWriter::WAVWriter(int sampleRate, int numChannels, int bitDepth) : splitFileButton("Split File into Channels"), filePicker("Choose a place to save", File(), "*.wav", true, true, nullptr)
{
    setSize(50, 20);
    
    addAndMakeVisible(splitFileButton);
    splitFileButton.addListener(this);
    //wav.createWriterFor(fileStream, <#double sampleRateToUse#>, <#unsigned int numberOfChannels#>, <#int bitsPerSample#>, <#const StringPairArray &metadataValues#>, <#int qualityOptionIndex#>)
}

WAVWriter::~WAVWriter()
{
}

void WAVWriter::paint (Graphics& g)
{
    
}

void WAVWriter::resized()
{
    splitFileButton.setBounds(0, 0, 50, 30);
}

void WAVWriter::buttonClicked(Button* button)
{
    if(button == &splitFileButton)
    {
        if(filePicker.browseForDirectory() == true)
        {
            chosenDirectory = filePicker.getResult();
            
            if(chosenDirectory.isDirectory() == true)
            {
                DBG("Directory picked at: " << chosenDirectory.getFullPathName());
            }
            else
            {
                DBG("Error - Directory not picked");
            }
        }
    }
}
