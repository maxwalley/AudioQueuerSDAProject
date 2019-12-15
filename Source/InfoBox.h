/*
  ==============================================================================

    InfoBox.h
    Created: 14 Dec 2019 7:42:31pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "ItemDataStruct.h"
#include "InfoSection.h"
#include "AudioWaveform.h"

//==============================================================================
/*
*/
class InfoBox    : public Component
{
public:
    InfoBox(AudioFormatManager &manager);
    ~InfoBox();

    void paintOverChildren (Graphics&) override;
    void resized() override;
    
    /**Changes the data that is shown in the info box*/
    void changeData(ItemInfo currentDataStruct);

private:
    Label headerLabel;
    
    InfoSection fileNameSection;
    InfoSection filePathSection;
    InfoSection fileSizeSection;
    InfoSection fileLengthSection;
    InfoSection fileSampleRateSection;
    InfoSection fileNumChannelsSection;
    
    AudioWaveform waveform;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoBox)
};
