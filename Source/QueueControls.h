/*
  ==============================================================================

    QueueControls.h
    Created: 22 Dec 2019 6:41:33pm
    Author:  Maximillian Walley

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class QueueControls    : public Component
{
public:
    
    /**The toggle buttons held by this component
     
     @see changeToggleState
     */
    enum ControlToggleButtons
    {
        loopQueue = 1,
        shuffleQueue = 2,
        playContinuously = 3
    };
    
    
    /**Constructor*/
    QueueControls();
    
    /**Destructor*/
    ~QueueControls();

    /**Implementation of the Component method*/
    void paint(Graphics& g) override;
    
    /**Implementation of the Component method*/
    void resized() override;
    
    /**Returns the state of the loop queue toggle button
     
     @returns the state of the loop queue toggle button
     */
    bool getLoopQueueButtonState();

    /**Returns the state of the shuffle queue toggle button
     
     @returns the state of the shuffle queue toggle button
     */
    bool getShuffleQueueButtonState();
    
    /**Returns the state of the play continuously toggle button
     
     @returns the state of the continuous toggle button
     */
    bool getContinuousButtonState();
    
    /**Changes the toggle state of one of the controls
     
     @param control         the control to change the toggle state of
     */
    void changeToggleState(int control);
    
    TextButton openFileButton;
    
private:
    ToggleButton loopQueueButton;
    Label loopQueueLabel;
    
    ToggleButton shuffleQueueButton;
    Label shuffleQueueLabel;
    
    ToggleButton playContinuouslyButton;
    Label playContinuouslyLabel;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (QueueControls)
};
