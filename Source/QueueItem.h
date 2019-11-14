/*
  ==============================================================================

    QueueItem.h
    Created: 14 Nov 2019 12:47:10pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

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
    
    void setItemIndex(int index);
    int getItemIndex();
    
    void setFile(File* file);
    
    String getFileName();

private:
    int itemIndex;
    File currentFile;
    int length;
    int sampleRate;
    int numChannels;
    bool lastId;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueItem)
};
