/*
  ==============================================================================

    QueueItem.h
    Created: 14 Nov 2019 12:47:10pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PlayButton.h"

//==============================================================================
/*
*/
class QueueItem : public Component
{
public:
    QueueItem(int idNum, File* file);
    ~QueueItem();

    void paint (Graphics&) override;
    void resized() override;
    
    void setFile(File* file);
    
    void setItemIndex(int index);
    int getItemIndex()const ;
    
    String getFileName();
    
    int64_t getFileSize();
    
    String getLengthInTime();
    
    Label* getPlayTimeLabel();
    Label* getStopTimeLabel();
    
    PlayButton* getPlayButton();
    
    void setSelected(bool isSelected);
    void setLast(bool last);

private:
    int itemIndex;
    File currentFile;
    int64_t size;
    
    Label playTimeLabel;
    Label stopTimeLabel;
    
    PlayButton playButton;
    
    AudioFormatReader* reader;
    int64_t lengthInSamples;
    double sampleRate;
    int numChannels;
    
    bool selected;
    bool lastId;
    
    void workOutLengthInSecs();
    int lengthInSecs;
    void workOutTime();
    String lengthInTime;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueItem)
};
