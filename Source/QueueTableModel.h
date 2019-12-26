/*
  ==============================================================================

    QueueTableModel.h
    Created: 19 Nov 2019 4:50:50pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "QueueItem.h"
#include "QueueTableHeader.h"
#include "ItemDataStruct.h"
#include "QueueControls.h"

//==============================================================================
/*
*/
class QueueTableModel    : public TableListBoxModel,
                           public Component,
                           public ActionBroadcaster,
                           public ActionListener
{
public:
    QueueTableModel();
    ~QueueTableModel();
    
    void resized() override;
    
    TableListBox embeddedTable;
    
    Array<QueueItem*> items;
    AudioTransportSource transport;

    /**Adds a new item to the array of items*/
    void addNewItem(File* file);
    
    /**Deletes the currently selected item from the array of items*/
    void deleteSelectedItem();
    
    int getSelectedRow();
    
    /**Moves the audio transport onto the next item in the queue. If there are no more items to play it will stop the queue
     Parameters:
     bool ignoreLooping - true if the looping mechanism wants to be ignored, false if not*/
    void moveTransportOn(bool ignoreLooping);
    
    /**Moves the audio transport back to the last item in the queue. If there is nothing before it will stop the queue */
    void moveTransportBack();
    
    void startQueue();
    
    int getCurrentStopPoint() const;
    void stopPointReached();
    
    File* getCurrentPlayingFile() const;
    
    /**Returns true if and item is playing, false if not*/
    bool itemPlaying() const;
    
    /**Returns the info of the current playing item in a struct*/
    ItemInfo getCurrentPlayingDataStruct() const;
    
    /**Returns the info of the current playing item in a struct*/
    ItemInfo getCurrentSelectedDataStruct() const;
    
    /**Sets the transports position*/
    void setTransportPosition(double newPosition);
    
    /**Updates the data struct of the currently selected item with the new loop toggle selection*/
    void updateSelectedItemLoopToggle(bool newLoopToggle);
    
    /**Updates the data struct of the currently selected item with the new loop toggle selection*/
    void updateSelectedItemNumLoops(int newNumLoops);
    
    QueueControls queueControls;
    
    private:
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;

    void selectedRowsChanged(int lastRowSelected) override;
    
    int currentIndexPlaying;
    int currentIndexSelected;
    
    int loopCounter;
    
    void setUpTransport(int indexToPlay);
    
    void actionListenerCallback(const String &message) override;
    
    QueueTableHeader header;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueTableModel)
};
