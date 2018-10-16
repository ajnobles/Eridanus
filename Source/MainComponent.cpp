/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{

    setSize (1600, 800);

    // SynthModulesScene
    addAndMakeVisible(Synth);

    // Keyboard
    addAndMakeVisible(KeyboardScene);
}

MainComponent::~MainComponent()
{
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
/*
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
*/
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    // SynthScene.setBounds (0, 0, getWidth(), getHeight() / 2.0f);
    // KeyboardScene.setBounds (0, getHeight() / 2.0f, getWidth(), getHeight() / 2.0f);

    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = { Track (2_fr), Track (1_fr) };
    grid.templateColumns = { Track (1_fr) };

    grid.items = { GridItem (Synth) , GridItem (KeyboardScene) };

    grid.performLayout (getLocalBounds());
}
