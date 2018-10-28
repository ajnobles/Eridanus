/*
  ==============================================================================

    SynthTitleScene.cpp
    Created: 16 Oct 2018 10:54:03am
    Author:  allen

  ==============================================================================
*/

#include "SynthScene.h"

//==============================================================================

SynthScene::SynthTitleScene::SynthTitleScene()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
}

SynthScene::SynthTitleScene::~SynthTitleScene()
{
}

void SynthScene::SynthTitleScene::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.setColour (BORDER_COLOR);
    g.setFont (20.0f);
    g.drawText ("ERIDANUS", getLocalBounds(), Justification::centred, true);
}

void SynthScene::SynthTitleScene::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.

}
