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
class InfoBox    : public Component,
                   public Button::Listener,
                   public ActionBroadcaster,
                   public Label::Listener
{
public:
    InfoBox(AudioFormatManager &manager);
    ~InfoBox();

    void paint(Graphics& g) override;
    void paintOverChildren(Graphics& g) override;
    void resized() override;
    
    /**Changes the data that is shown in the info box*/
    void changeData(ItemInfo currentDataStruct);
    
    /**Returns the loop button state*/
    bool getLoopButtonState() const;
    
    /**Returns new number of loops*/
    int getNewNumLoops() const;
    
private:
    Label headerLabel;
    
    InfoSection fileNameSection;
    InfoSection filePathSection;
    InfoSection fileSizeSection;
    InfoSection fileLengthSection;
    InfoSection fileSampleRateSection;
    InfoSection fileNumChannelsSection;
    
    Label loopDescriptionLabel;
    ToggleButton loopToggle;
    
    Label loopNumDescriptionLabel;
    Label loopNumDataLabel;
    
    /**Overriden from Button::Listener*/
    void buttonClicked(Button* button) override;
    
    /**Overidden from Label::Listener*/
    void labelTextChanged(Label* labelThatHasChanged) override;
    
    int newNumLoops;
    
    TextButton deleteButton;
    
    AudioWaveform waveform;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoBox)
};
