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
    /**Constructor
     
     @param manager         the AudioFormatManager to use
     */
    InfoBox(AudioFormatManager &manager);
    
    /**Destructor*/
    ~InfoBox();

    /**Implementation of the Component method*/
    void paint(Graphics& g) override;
    
    /**Implementation of the Component method*/
    void paintOverChildren(Graphics& g) override;
    
    /**Implementation of the Component method*/
    void resized() override;
    
    /**Changes the data that is shown in the info box
     
     @param currentDataStruct           the data to show
     */
    void changeData(ItemInfo currentDataStruct);
    
    /**Returns the loop button state of the current data being shown
     
     @return the loop button state
     */
    bool getLoopButtonState() const;
    
    /**Returns number of loops of the current data being shown
     
     @return the number of loops
     */
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
    
    /**Implementation of the Button::Listener method*/
    void buttonClicked(Button* button) override;
    
    /**Implementation of the Label::Listener method*/
    void labelTextChanged(Label* labelThatHasChanged) override;
    
    int newNumLoops;
    
    TextButton deleteButton;
    
    AudioWaveform waveform;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (InfoBox)
};
