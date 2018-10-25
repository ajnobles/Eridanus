/*
  ==============================================================================

    LFOModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "SynthScene.h"


SynthScene::SynthModulesScene::LFOModule::LFOModule() 
{
    //
    
    addAndMakeVisible ( RateSlider );
    RateSlider.setRange ( 0, 100 );
    RateSlider.setSliderStyle ( Slider::LinearVertical );
    RateSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
   

    addAndMakeVisible ( DepthSlider );
    DepthSlider.setRange ( 0, 100 );
    DepthSlider.setSliderStyle ( Slider::LinearVertical );
    DepthSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

}


SynthScene::SynthModulesScene::LFOModule::~LFOModule() 
{
    //
}


void SynthScene::SynthModulesScene::LFOModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR);

    CustomComponent::buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

    // TEMP IDENTIFICATION TEXT
    g.drawText ("LFO", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

}



void SynthScene::SynthModulesScene::LFOModule::resized ()
{
    // 
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { Track (1_fr), Track (10_fr) };
    grid.templateColumns = { Track (1_fr), Track (1_fr) };

    grid.items = {
        GridItem ( nullptr ), 
        GridItem ( nullptr ), 
        GridItem ( RateSlider ),
        GridItem ( DepthSlider )
    };

    Rectangle <int> bounds = getLocalBounds();
    bounds = moduleInternalsBounds ( bounds, 
                                     MODULE_INSIDE_OFFSET, 
                                     OFFSET, 
                                     THICKNESS);

    grid.performLayout ( bounds );

}
