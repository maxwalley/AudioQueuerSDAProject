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
#include "ItemDataStruct.h"

//==============================================================================
/*
*/
class QueueItem : public Component,
                  public Label::Listener,
                  public Button::Listener,
                  public ActionBroadcaster
{
public:
    QueueItem(int idNum, File* file);
    ~QueueItem();

    void paint (Graphics&) override;
    
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
    
    double getSampleRate();
    int getNumChannels();
    
    int getPlayPoint();
    int getStopPoint();
    
    ItemInfo getItemData() const;
    
    /**Sets whether the item loops or not*/
    void setLoop(bool loop);
    
    /**Returns whether the item is set to loop or not*/
    bool getLoop() const;
    
    /**Sets the amount of loops the item does*/
    void setNumLoops(int numLoops);
    
    /**Returns the amount of loops this item is set to perform*/
    int getNumLoops() const;

private:
    
    ItemInfo itemData;
    
    Label playTimeLabel;
    Label stopTimeLabel;
    void labelTextChanged(Label* labelThatHasChanged) override;
    
    PlayButton playButton;
    void buttonClicked(Button* button) override;
    
    void workOutLengthInSecs();
    //int lengthInSecs;
    void workOutTime();
    //String lengthInTime;
    
    struct labelTimes
    {
        int preColonNum;
        int postColonNum;
    };
    
    labelTimes playLabelTime;
    labelTimes stopLabelTime;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueItem)
};
