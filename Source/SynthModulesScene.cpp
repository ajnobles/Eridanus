/*
  ==============================================================================

    SynthModulesScene.cpp
    Created: 12 Oct 2018 11:28:14am
    Author:  allen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthModulesScene.h"

//==============================================================================
SynthModulesScene::SynthModulesScene()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible( Output );
}

SynthModulesScene::~SynthModulesScene()
{
}

void SynthModulesScene::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    // g.fillAll (Colours::lightblue);
    

    // BUILD SYNTH MODULE BORDER
    g.setColour (Colours::white);

    CustomComponent::buildRoundedRectangle (g, CORNERSIZE, THICKNESS, OFFSET);

    // TEMP TEXT
    g.setFont (Font (16.0f));
    g.setColour (Colours::red);
    g.drawText ("SYNTH MODULES", getLocalBounds(), Justification::centred, true);
}

void SynthModulesScene::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains.

    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = { Track (1_fr) };
    grid.templateColumns = { Track (10_fr), Track (1_fr)  };

    grid.items = { GridItem (nullptr), GridItem (Output) };

    grid.performLayout ( getLocalBounds() );

}

