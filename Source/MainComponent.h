/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioTable.h"
#include "AudioWaveform.h"
#include "FFT.h"
#include "AudioPlayerGUI.h"
#include "InfoBox.h"
#include "Menu.h"
#include "AudioPlayer.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener,
                        public Slider::Listener,
                        public Timer,
                        public ActionListener,
                        public MenuBarModel
{
public:
    //==============================================================================
    /**Constructor*/
    MainComponent();
    
    /**Destructor*/
    ~MainComponent();

    //==============================================================================
    /**Implementation of the AudioSource method*/
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    
    /**Implementation of the AudioSource method*/
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    
    /**Implementation of the AudioSource method*/
    void releaseResources() override;

    //==============================================================================
    /**Implementation of the Component method*/
    void paint (Graphics& g) override;
    
    /**Implementation of the Component method*/
    void resized() override;
    
    //==============================================================================
    /**Implementation of the MenuBarModel method*/
    StringArray getMenuBarNames() override;
    
    /**Implementation of the MenuBarModel method*/
    PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName) override;
    
    /**Implementation of the MenuBarModel method*/
    void menuItemSelected (int menuItemID, int topLevelMenuIndex) override;
    
    
private:
    //==============================================================================
    // Your private member variables go here...

    AudioPlayer player;
    
    FileChooser fileChooser;
    File selectedFile;

    bool fileLoaded;
    
    /**Implementation of the Button::Listener method*/
    void buttonClicked(Button* button) override;
    
    /**Implementation of the Slider::Listener method*/
    void sliderValueChanged(Slider* slider) override;
    
    /**Adds a file to the queue using a FileChooser
     
     @see FileChooser
     */
    void addFile();
    
    /**Plays the queue*/
    void playQueue();
    
    /**Pauses the queue*/
    void pauseAudio();
    
    /**Stops the queue*/
    void stopAudio();
    
    /**Implementation of the Timer method*/
    void timerCallback() override;
    int timerCount;
    
    /**Implementation of the MouseListener method*/
    void mouseDown (const MouseEvent &event) override;
    
    /**Changes the current position in the audio stream
     called when the AudioWaveform is clicked on
     
     @param xAxis           the x axis position of the click on the waveform*/
    void changeAudioPosition(int xAxis);
    
    AudioWaveform waveform;
    
    FFT transformImage;    
    AudioPlayerGUI playerGUI;
    
    AudioTable table;
    
    /**Implementation of the ActionListener method*/
    void actionListenerCallback(const String& message) override;
    
    /**Sets up the audio player with the next file to play from the table*/
    void setUpPlayer();
    
    InfoBox infoBox;
    
    //Menu menu;
    
    MenuBarComponent menu;
    Component::SafePointer<ComponentWindow> selectorWindow;
    Component::SafePointer<AudioDeviceSelectorComponent> selector;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
