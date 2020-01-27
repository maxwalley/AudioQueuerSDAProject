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
    loopToggle.setEnabled(false);
    loopToggle.setVisible(false);
    
    addAndMakeVisible(loopNumDescriptionLabel);
    loopNumDescriptionLabel.setText("Number of Loops", dontSendNotification);
    
    addAndMakeVisible(loopNumDataLabel);
    loopNumDataLabel.setEnabled(false);
    loopNumDataLabel.setText("0", dontSendNotification);
    loopNumDataLabel.addListener(this);
    loopNumDataLabel.setVisible(false);
    loopNumDataLabel.setEditable(true);
    
    addAndMakeVisible(deleteButton);
    deleteButton.addListener(this);
    deleteButton.setEnabled(false);
    
    addAndMakeVisible(waveform);
    waveform.setAlwaysOnTop(true);
}

InfoBox::~InfoBox()
{
}

void InfoBox::paint(Graphics& g)
{
    g.fillAll(Colours::white);
    
    g.setColour(Colours::grey);
    g.fillRect(0, 275, getWidth(), 100);
    
    headerLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    
    loopDescriptionLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    
    loopNumDescriptionLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    loopNumDataLabel.setColour(Label::ColourIds::textColourId, Colours::black);
    
    deleteButton.setColour(TextButton::ColourIds::buttonColourId, Colours::lightgrey);
    deleteButton.setColour(TextButton::ColourIds::textColourOnId, Colours::black);
    deleteButton.setColour(TextButton::ColourIds::textColourOffId, Colours::black);
}

void InfoBox::paintOverChildren (Graphics& g)
{
    //Draws the outer container
    g.drawRect(0, 0, getWidth(), getHeight(), 4);
    
    //Draws the inner parts that the info sections dont draw
    g.drawLine(0, 45, 200, 45);
    g.drawLine(100, 45, 100, 50);
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
    //Changes the data section for all the info sections based on whats in the struct passed to it
    fileNameSection.setData(currentDataStruct.fileName);
    filePathSection.setData(currentDataStruct.file.getFullPathName());
    fileSizeSection.setData(String(currentDataStruct.size));
    fileLengthSection.setData(currentDataStruct.lengthInTime);
    fileSampleRateSection.setData(String(currentDataStruct.sampleRate));
    fileNumChannelsSection.setData(String(currentDataStruct.numChannels));
    
    //Checks if the loop option in the struct is true
    if(currentDataStruct.loop == true)
    {
        //Changes the loop button and num loops label accordingly
        loopToggle.setToggleState(true, dontSendNotification);
        loopNumDataLabel.setEnabled(true);
        loopNumDataLabel.setVisible(true);
        loopNumDataLabel.setText(String(currentDataStruct.numLoops), dontSendNotification);
    }
    else
    {
        //Changes the loop button and num loops label accordingly
        loopToggle.setToggleState(false, dontSendNotification);
        loopNumDataLabel.setText("0", dontSendNotification);
    }
    
    repaint();
    
    //Resets this to keep track if a new value is entered into the numloops label
    newNumLoops = 0;
    
    //Sets the waveform to the file in the struct
    waveform.set(new FileInputSource(currentDataStruct.file));
    
    loopToggle.setEnabled(true);
    loopToggle.setVisible(true);
    loopNumDataLabel.setVisible(true);
    
    deleteButton.setEnabled(true);
}

bool InfoBox::getLoopButtonState() const
{
    return loopToggle.getToggleState();
}

int InfoBox::getNewNumLoops() const
{
    return newNumLoops;
}

void InfoBox::clear()
{
    //Clears all the infoSections
    fileNameSection.clear();
    filePathSection.clear();
    fileSizeSection.clear();
    fileLengthSection.clear();
    fileSampleRateSection.clear();
    fileNumChannelsSection.clear();
    
    //Resets the loop button and the numloops label accordingly
    loopToggle.setEnabled(false);
    loopToggle.setVisible(false);
    loopNumDataLabel.setEnabled(false);
    loopNumDataLabel.setVisible(false);
    
    waveform.clear();
    
    deleteButton.setEnabled(true);
    
    repaint();
}

void InfoBox::buttonClicked(Button* button)
{
    //Loop button
    if(button == &loopToggle)
    {
        sendActionMessage("Loop button changed");
        
        //Checks what its states been changed to and changes the button and the num loop labels settings accordinly
        if(getLoopButtonState() == true)
        {
            loopNumDataLabel.setEnabled(true);
        }
        
        else if(getLoopButtonState() == false)
        {
            loopNumDataLabel.setEnabled(false);
            loopNumDataLabel.setText("0", dontSendNotification);
            loopNumDataLabel.repaint();
        }
    }
    
    //Delete button
    else if(button == &deleteButton)
    {
        //Opens an alert window to make sure the user wants to delete this item. Checks what their input to this alert window is
        if(AlertWindow::showOkCancelBox(AlertWindow::AlertIconType::WarningIcon, "Delete from Queue?", "Are you sure you want to delete this item from the queue?", "Yes", "No") == true)
        {
            sendActionMessage("Delete button pressed");
        }
    }
}

void InfoBox::labelTextChanged(Label* labelThatHasChanged)
{
    //NumLoops label
    if(labelThatHasChanged == &loopNumDataLabel)
    {
        String newText = loopNumDataLabel.getText();
        int textLength = newText.length();
        
        //Iterates through the characters of the new text of the label
        for(int currentIndex = 0; currentIndex < textLength; currentIndex++)
        {
            String currentChar = String::charToString(newText[currentIndex]);
            
            //Checks for anything other than a digit
            if(currentChar.compare("0") != 0 && currentChar.compare("1") != 0 && currentChar.compare("2") != 0 && currentChar.compare("3") != 0 && currentChar.compare("4") != 0 && currentChar.compare("5") != 0 && currentChar.compare("6") != 0 && currentChar.compare("7") != 0 && currentChar.compare("8") != 0 && currentChar.compare("9") != 0)
            {
                //Resets the label to blank if it finds anything other than a digit
                loopNumDataLabel.setText("", dontSendNotification);
            }
            
            else
            {
                //Keeps track of what the new number of loops entered is
                newNumLoops = newText.getIntValue();
                sendActionMessage("Number of loops changed");
            }
        }
    }
}
