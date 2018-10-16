/*
  ==============================================================================

    SynthScene.cpp
    Created: 16 Oct 2018 10:29:28am
    Author:  allen

  ==============================================================================
*/

#include "SynthScene.h"

//==============================================================================

SynthScene::SynthScene()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible( TitleScene );
    addAndMakeVisible( ModulesScene );
    addAndMakeVisible( Utilities );
}

SynthScene::~SynthScene()
{
}

void SynthScene::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void SynthScene::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.

    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = { Track (1_fr), Track (10_fr), Track (1_fr) };
    grid.templateColumns = {
        Track (1_fr)
    };

    grid.items = { 
        GridItem (TitleScene),
        GridItem (ModulesScene), 
        GridItem (Utilities)
    };

    grid.performLayout ( getLocalBounds() );

}

