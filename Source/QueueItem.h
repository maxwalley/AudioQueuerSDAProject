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
class QueueItem : public Label::Listener,
                  public Button::Listener,
                  public ActionBroadcaster
{
public:
    /**Constructor
     
     @param idNum           the index number that this QueueItem will have
     @param file            the file this QueueItem will hold. This can also be set in setFile
     
     @see setItemIndex
     @see setFile
     */
    QueueItem(int idNum, File* file);
    
    /**Destructor*/
    ~QueueItem();
    
    /**Sets the file this QueueItem will hold
     
     @param file            the file this QueueItem will hold
     */
    void setFile(File* file);
    
    /**Returns the file this QueueItem holds
     
     @return the file this QueueItem holds
     
     @see setFile
     */
    File* getFile();
    
    /**Sets the index of this QueueItem
     
     @param index           the new index to set this QueueItem as
     */
    void setItemIndex(int index);
    
    /**Returns the index of this QueueItem
     
     @return the index of this QueueItem
     
     @see setItemIndex
     */
    int getItemIndex() const ;
    
    /**Returns the name of the file this QueueItem is associated with
     
     @return the name of the file this QueueItem is associated with
     */
    String getFileName() const;
    
    /**Returns the size of the file this QueueItem is associated with
     
     @return the size of the file this QueueItem is associated with
     */
    int64_t getFileSize() const;
    
    /**Returns the length of the file associated with this QueueItem as a string
     
     @return the length of the file associated with this QueueItem as a string
     */
    String getLengthInTime();
    
    /**Returns the play time label
     
     @return the play time label
     */
    Label* getPlayTimeLabel();
    
    /**Returns the stop time label
     
     @Return the stop time label
     */
    Label* getStopTimeLabel();
    
    /**Returns the play button
     
     @return the play button
     */
    PlayButton* getPlayButton();
    
    /**Returns the play point set for this QueueItem in seconds
     
     @return the play point for this QueueItem in seconds
     */
    int getPlayPoint() const;
    
    /**Returns the stop point for this QueueItem in seconds
     
     @return the stop point for this QueueItem in seconds*/
    int getStopPoint() const;
    
    /**Returns the item data for this QueueItem as an ItemInfo struct
     
     @return the item data for this QueueItem as an ItemInfo struct
     */
    ItemInfo getItemData() const;
    
    /**Sets whether this QueueItem loops or not
     
     @param loop            whether to loop this QueueItem
     */
    void setLoop(bool loop);
    
    /**Returns whether this QueueItem is set to loop
     
     @return whether this QueueItem is set to loop
     
     @see setLoop
     */
    bool getLoop() const;
    
    /**Sets the amount of times this QueueItem should loop
     
     @param numLoops            the number of loops this QueueItem should do
     */
    void setNumLoops(int numLoops);
    
    /**Returns the amount of times this QueueItem is set to loop
     
     @return the amount of times this QueueItem is set to loop
     
     @see setNumLoops
     */
    int getNumLoops() const;

private:
    
    ItemInfo itemData;
    
    AudioFormatManager formatManager;
    AudioFormatReader* reader;
    
    Label* playTimeLabel;
    Label* stopTimeLabel;
    
    /**Implementation of the Label::Listener method*/
    void labelTextChanged(Label* labelThatHasChanged) override;
    
    PlayButton* playButton;
    
    /**Implementation of the Button::Listener method*/
    void buttonClicked(Button* button) override;
    
    /**Works out the length of the QueueItems file in seconds*/
    void workOutLengthInSecs();
    
    /**Works out the length of the QueueItems file and turns it into a string*/
    void workOutTime();
    
    struct labelTimes
    {
        int preColonNum;
        int postColonNum;
    };
    
    labelTimes playLabelTime;
    labelTimes stopLabelTime;
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueItem)
};
