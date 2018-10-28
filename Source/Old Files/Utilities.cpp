/*
  ==============================================================================

    Utilities.cpp
    Created: 16 Oct 2018 11:07:40am
    Author:  allen

  ==============================================================================
*/

#include "SynthScene.h"

//==============================================================================

SynthScene::GUIUtilities::GUIUtilities()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    
    addAndMakeVisible ( Presets );
    addAndMakeVisible ( MidiChannel );
}

SynthScene::GUIUtilities::~GUIUtilities()
{
}

void SynthScene::GUIUtilities::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    g.setColour (Colours::white);

}

void SynthScene::GUIUtilities::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.

    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = { Track (1_fr) };
    grid.templateColumns = { Track (1_fr), Track (10_fr), Track (1_fr) };

    grid.items = {
        GridItem ( Presets ),
        GridItem ( nullptr ),
        GridItem ( MidiChannel ),
    };

    grid.performLayout (getLocalBounds());
}

SynthScene::GUIUtilities::Selectors::Selectors () {}

SynthScene::GUIUtilities::Selectors::~Selectors () {}

void SynthScene::GUIUtilities::Selectors::paint (Graphics& g)
{
    g.setColour(Colours::white);

    g.setFont (14.0f);
    g.drawText ("Selector", getLocalBounds(),  Justification::centred, true);
}    

void SynthScene::GUIUtilities::Selectors::resized () {}

