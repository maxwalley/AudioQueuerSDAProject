/*
  ==============================================================================

    InfoBox.cpp
    Created: 14 Dec 2019 7:42:31pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "InfoBox.h"

//==============================================================================
InfoBox::InfoBox(AudioFormatManager &manager) : fileNameSection("File Name"), filePathSection("File Path"), fileSizeSection("File Size (Bytes)"), fileLengthSection("File Length"), fileSampleRateSection("Sample Rate"), fileNumChannelsSection("Number of Channels"), newNumLoops(0), deleteButton("Delete"), waveform(manager)
{
    setSize(200, 525);
    
    addAndMakeVisible(headerLabel);
    headerLabel.setText("Selected Item Info", dontSendNotification);
    headerLabel.setJustificationType(Justification::centred);
    headerLabel.setFont(Font(20));
    
    addAndMakeVisible(fileNameSection);
    addAndMakeVisible(filePathSection);
    addAndMakeVisible(fileSizeSection);
    addAndMakeVisible(fileLengthSection);
    addAndMakeVisible(fileSampleRateSection);
    addAndMakeVisible(fileNumChannelsSection);
    
    addAndMakeVisible(loopDescriptionLabel);
    loopDescriptionLabel.setText("Loop?", dontSendNotification);
    addAndMakeVisible(loopToggle);
    
    loopToggle.addListener(this);
    
    addAndMakeVisible(loopNumDescriptionLabel);
    loopNumDescriptionLabel.setText("Number of Loops", dontSendNotification);
    
    addAndMakeVisible(loopNumDataLabel);
    loopNumDataLabel.setEditable(false);
    loopNumDataLabel.setText("0", dontSendNotification);
    loopNumDataLabel.addListener(this);
    
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    
    addAndMakeVisible(waveform);
}

InfoBox::~InfoBox()
{
}

void InfoBox::paintOverChildren (Graphics& g)
{
    g.drawRoundedRectangle(0, 0, 200, 550, 10, 4);
    
    g.drawLine(100, 275, 100, 350);
    g.drawLine(0, 300, 200, 300);
    g.drawLine(0, 350, 200, 350);
}

void InfoBox::resized()
{
    headerLabel.setBounds(0, 0, 200, 45);
    
    fileNameSection.setBounds(0, 50, 200, 50);
    filePathSection.setBounds(0, 100, 200, 50);
    fileSizeSection.setBounds(0, 150, 200, 25);
    fileLengthSection.setBounds(0, 175, 200, 25);
    fileSampleRateSection.setBounds(0, 200, 200, 25);
    fileNumChannelsSection.setBounds(0, 225, 200, 50);
    
    loopDescriptionLabel.setBounds(0, 275, 100, 25);
    loopToggle.setBounds(140, 277.5, 20, 20);
    
    loopNumDescriptionLabel.setBounds(0, 300, 100, 50);
    loopNumDataLabel.setBounds(100, 300, 100, 50);
    
    deleteButton.setBounds(0, 350, 200, 25);
    
    waveform.setBounds(0, 375, 200, 150);
}

void InfoBox::changeData(ItemInfo currentDataStruct)
{
    fileNameSection.setData(currentDataStruct.file->getFileName());
    filePathSection.setData(currentDataStruct.file->getFullPathName());
    fileSizeSection.setData(String(currentDataStruct.size));
    fileLengthSection.setData(currentDataStruct.lengthInTime);
    fileSampleRateSection.setData(String(currentDataStruct.sampleRate));
    fileNumChannelsSection.setData(String(currentDataStruct.numChannels));
    
    if(currentDataStruct.loop == true)
    {
        loopToggle.setToggleState(true, dontSendNotification);
        loopNumDataLabel.setText(String(currentDataStruct.numLoops), dontSendNotification);
    }
    else
    {
        loopToggle.setToggleState(false, dontSendNotification);
        loopNumDataLabel.setText("0", dontSendNotification);
    }
    
    repaint();
    
    newNumLoops = 0;
    
    waveform.set(new FileInputSource(*currentDataStruct.file));
}

bool InfoBox::getLoopButtonState() const
{
    return loopToggle.getToggleState();
}

int InfoBox::getNewNumLoops() const
{
    return newNumLoops;
}

void InfoBox::buttonClicked(Button* button)
{
    if(button == &loopToggle)
    {
        sendActionMessage("Loop button changed");
        
        if(getLoopButtonState() == true)
        {
            loopNumDataLabel.setEditable(true);
        }
        
        else if(getLoopButtonState() == false)
        {
            loopNumDataLabel.setEditable(false);
            loopNumDataLabel.setText("0", dontSendNotification);
            loopNumDataLabel.repaint();
        }
    }
    
    else if(button == &deleteButton)
    {
        //Opens an alert window to make sure the user wants to delete this item
        if(AlertWindow::showOkCancelBox(AlertWindow::AlertIconType::WarningIcon, "Delete from Queue?", "Are you sure you want to delete this item from the queue?", "Yes", "No") == true)
        {
            sendActionMessage("Delete button pressed");
        }
    }
}

void InfoBox::labelTextChanged(Label* labelThatHasChanged)
{
    if(labelThatHasChanged == &loopNumDataLabel)
    {
        String newText = loopNumDataLabel.getText();
        int textLength = newText.length();
        
        for(int currentIndex = 0; currentIndex < textLength; currentIndex++)
        {
            String currentChar = String::charToString(newText[currentIndex]);
            
            //Checks for anything other than a digit
            if(currentChar.compare("0") != 0 && currentChar.compare("1") != 0 && currentChar.compare("2") != 0 && currentChar.compare("3") != 0 && currentChar.compare("4") != 0 && currentChar.compare("5") != 0 && currentChar.compare("6") != 0 && currentChar.compare("7") != 0 && currentChar.compare("8") != 0 && currentChar.compare("9") != 0)
            {
                loopNumDataLabel.setText("", dontSendNotification);
            }
            
            else
            {
                newNumLoops = newText.getIntValue();
                sendActionMessage("Number of loops changed");
            }
        }
    }
}
