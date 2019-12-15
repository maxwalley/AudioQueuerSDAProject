/*
  ==============================================================================

    InfoBox.cpp
    Created: 14 Dec 2019 7:42:31pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "InfoBox.h"

//==============================================================================
InfoBox::InfoBox() : fileNameSection("File Name"), filePathSection("File Path"), fileSizeSection("File Size (Bytes)"), fileLengthSection("File Length"), fileSampleRateSection("Sample Rate"), fileNumChannelsSection("Number of Channels")
{
    setSize(200, 500);
    
    addAndMakeVisible(fileNameSection);
    addAndMakeVisible(filePathSection);
    addAndMakeVisible(fileSizeSection);
    addAndMakeVisible(fileLengthSection);
    addAndMakeVisible(fileSampleRateSection);
    addAndMakeVisible(fileNumChannelsSection);
}

InfoBox::~InfoBox()
{
}

void InfoBox::paintOverChildren (Graphics& g)
{
    g.drawRoundedRectangle(0, 0, 200, 500, 10, 4);
}

void InfoBox::resized()
{
    fileNameSection.setBounds(0, 0, 200, 50);
    filePathSection.setBounds(0, 50, 200, 50);
    fileSizeSection.setBounds(0, 100, 200, 50);
    fileLengthSection.setBounds(0, 150, 200, 50);
    fileSampleRateSection.setBounds(0, 200, 200, 50);
    fileNumChannelsSection.setBounds(0, 250, 200, 50);
}

void InfoBox::changeData(ItemInfo currentDataStruct)
{
    fileNameSection.setData(currentDataStruct.file->getFileName());
    filePathSection.setData(currentDataStruct.file->getFullPathName());
    fileSizeSection.setData(String(currentDataStruct.size));
    fileLengthSection.setData(currentDataStruct.lengthInTime);
    fileSampleRateSection.setData(String(currentDataStruct.sampleRate));
    fileNumChannelsSection.setData(String(currentDataStruct.numChannels));
    repaint();
}
