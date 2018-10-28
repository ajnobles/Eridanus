/*
  ==============================================================================

    SynthModulesScene.cpp
    Created: 12 Oct 2018 11:28:14am
    Author:  allen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthScene.h"

//==============================================================================
SynthScene::SynthModulesScene::SynthModulesScene()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible( Input );
    addAndMakeVisible( Output );
    addAndMakeVisible( AmpFilter );
    addAndMakeVisible( EnvFilter );
    addAndMakeVisible( LFO_Freq );
    addAndMakeVisible( LFO_Amp );
    addAndMakeVisible( Oscillator );
    addAndMakeVisible( Saturation );
}

SynthScene::SynthModulesScene::~SynthModulesScene()
{
}

void SynthScene::SynthModulesScene::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void SynthScene::SynthModulesScene::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.

    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = { Track (1_fr) };
    grid.templateColumns = {
        Track (1_fr),
        Track (1_fr),
        Track (2_fr),
        Track (1_fr),
        Track (2_fr),
        Track (2_fr),
        Track (1_fr),
        Track (1_fr),
    };

    grid.items = { 
        GridItem (Input),
        GridItem (LFO_Freq), 
        GridItem (Oscillator),
        GridItem (LFO_Amp),
        GridItem (EnvFilter),
        GridItem (AmpFilter),
        GridItem (Saturation),
        GridItem (Output)
    };

    grid.performLayout ( getLocalBounds() );

}

