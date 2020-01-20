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
class AudioTable    : public TableListBoxModel,
                      public Component,
                      public ActionBroadcaster,
                      public ActionListener
{
public:
    /**Constructor*/
    AudioTable();
    
    /**Destructor*/
    ~AudioTable();
    
    /**Implementation of the Component method*/
    void paint(Graphics& g) override;
    
    /**Implementation of the Component method*/
    void resized() override;
    
    QueueControls queueControls;
    OwnedArray<QueueItem, CriticalSection> items;

    /**Adds a new item to the array of items and displays it in the table
     
     @param file            the file to add
     */
    void addNewItem(File* file);
    
    /**Deletes the currently selected item from the array of items and from the table*/
    void deleteSelectedItem();
    
    /**Returns the row number of the current selected row
     
     @return the row number of the current selected row
     */
    int getSelectedRow();
    
    /**Moves the index to play onto the next QueueItem in the table, taking into account the toggle buttons on QueueControls*/
    void moveIndexToPlayOn();
    
    /**Moves the index to play back to the last QueueItem in the table. If the current playing index is the first in the table this will reset the index to play to nothing*/
    void moveIndexToPlayBack();
    
    /**Initilises next index to play in a variety of ways depending on QueueControls*/
    void startQueue();
    
    /**Returns the play point of the current QueueItem to play
     
     @return the play point of the current QueueItem to play
     */
    int getCurrentPlayPoint() const;
    
    /**Returns the stop point of the current QueueItem to play
    
    @return the stop point of the current QueueItem to play
    */
    int getCurrentStopPoint() const;
    
    /**Returns the file to play from specific QueueItem that should play next. If there is no item to play next this will return nullptr
    
    @return the file to play from specific QueueItem that should play next
    */
    File* getFileToPlay() const;
    
    /**Returns the info of the current QueueItem to play in an ItemInfo struct
     
     @return the info of the current QueueItem to play in an ItemInfo struct
     */
    ItemInfo getCurrentPlayingDataStruct() const;
    
    /**Returns the info of the current QueueItem selected in the table in an ItemInfo struct
    
    @return the info of the current QueueItem selected in an ItemInfo struct
    */
    ItemInfo getCurrentSelectedDataStruct() const;
    
    /**Changes the loop toggle of the ItemInfo struct of the currently selected item. Essentially changing whether the selected QueueItem loops or not
     
     @param newLoopToggle           the new loop toggle selection
     */
    void updateSelectedItemLoopToggle(bool newLoopToggle);
    
    /**Changes the amount of loops the currently selected QueueItem does by updating the number of loops in the items ItemInfo struct
     
     @param newNumLoops         the new amount of loops for this QueueItem to perform
     */
    void updateSelectedItemNumLoops(int newNumLoops);
    
    /** Changes the value of a toggle control in the Queue Controls
     
     @param control - the control to toggle. Set using ControlToggleButtons enum in QueueControls
     
     @see ControlToggleButtons
     */
    void changeQueueControlToggle(int control);
    
    /**Sets the index to play back to nothing*/
    void reset();
    
    private:
    
    TableListBox embeddedTable;

    /**Implementation of the TableListBoxModel method*/
    int getNumRows() override;
    
    /**Implementation of the TableListBoxModel method*/
    void paintRowBackground(Graphics& g, int rowNumber, int width, int height, bool rowIsSelected) override;
    
    /**Implementation of the TableListBoxModel method*/
    void paintCell(Graphics &g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) override;
    
    /**Implementation of the TableListBoxModel method*/
    Component* refreshComponentForCell(int rowNumber, int columnId, bool isRowSelected, Component* existingComponentToUpdate) override;
    
    /**Implementation of the TableListBoxModel method*/
    void selectedRowsChanged(int lastRowSelected) override;
    
    int indexToPlay;
    int currentIndexSelected;
    int nextIndexToPlay;
    
    int loopCounter;
    
    /**Implementation of the ActionListener method*/
    void actionListenerCallback(const String &message) override;
    
    QueueTableHeader header;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioTable)
};
