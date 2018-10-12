/*
  ==============================================================================

    KeyboardScene.cpp
    Created: 12 Oct 2018 12:38:56pm
    Author:  allen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "KeyboardScene.h"

//==============================================================================
KeyboardScene::KeyboardScene()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

KeyboardScene::~KeyboardScene()
{
}

void KeyboardScene::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    // g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (Colours::darkblue);
    g.setFont (16.0f);
    g.drawText ("KeyboardScene", getLocalBounds(),
                Justification::centred, true);   // draw some placeholder text
}

void KeyboardScene::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
