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

    void addNewItem(File* file);
    
    int getSelectedRow();
    
    void moveTransportOn();
    
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
    
    private:
    
    int getNumRows() override;
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    std::unique_ptr<AudioFormatReaderSource> audioFormatReaderSource;

    void selectedRowsChanged(int lastRowSelected) override;
    
    int currentIndexPlaying;
    int currentIndexSelected;
    
    void setUpTransport(int indexToPlay);
    
    void actionListenerCallback(const String &message) override;
    
    QueueTableHeader header;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueTableModel)
};
