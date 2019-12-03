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
class QueueItem : public Component,
                  public Label::Listener
{
public:
    QueueItem(int idNum, File* file);
    ~QueueItem();

    void paint (Graphics&) override;
    void resized() override;
    
    void setFile(File* file);
    File* getFile();
    
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
    
    //AudioTransportSource audioTransportSource;
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    
    double getReaderSampleRate();
    int getReaderNumChannels();

private:
    int itemIndex;
    File currentFile;
    int64_t size;
    
    Label playTimeLabel;
    Label stopTimeLabel;
    void labelTextChanged(Label* labelThatHasChanged) override;
    
    PlayButton playButton;
    
    AudioFormatReader* reader;
    int64_t lengthInSamples;
    double sampleRate;
    int numChannels;
    
    //std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;
    
    bool selected;
    bool lastId;
    
    void workOutLengthInSecs();
    int lengthInSecs;
    void workOutTime();
    String lengthInTime;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueItem)
};
