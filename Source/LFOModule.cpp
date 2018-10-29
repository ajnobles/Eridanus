/*
  ==============================================================================

    LFOModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "LFOModule.h"

LfoModule::LfoModule (Slider* rs, Slider* ds, String* lfoName)
    : RateSlider (rs), DepthSlider (ds), lfoType (lfoName)
{
    
    addAndMakeVisible ( RateSlider );
    RateSlider->setRange ( 0.0, 10.0 );
    RateSlider->setSliderStyle ( Slider::LinearVertical );
    RateSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
    RateSlider->setValue(1.0);
    
    addAndMakeVisible(RateLabel);
    RateLabel.setText("Rate", dontSendNotification);

    addAndMakeVisible ( DepthSlider );
    DepthSlider->setRange ( 0.0, 1.0 );
    DepthSlider->setSliderStyle ( Slider::LinearVertical );
    DepthSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );        
    DepthSlider->setValue(0.0); 
    
    addAndMakeVisible(DepthLabel);
    DepthLabel.setText("Depth", dontSendNotification);

}    
    
void LfoModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR);

    CustomComponent::buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

    // TEMP IDENTIFICATION TEXT
    g.drawText (*lfoType, 0, 25, getWidth(), getHeight(), Justification::centredTop); 

}

void LfoModule::resized ()
{
    // 
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { Track (1_fr), Track (10_fr), Track (1_fr) };
    grid.templateColumns = { Track (1_fr), Track (1_fr) };

    grid.items = {
        GridItem ( nullptr ), 
        GridItem ( nullptr ), 
        GridItem ( RateSlider ),
        GridItem ( DepthSlider ),
        GridItem ( RateLabel ),
        GridItem ( DepthLabel )
    };

    Rectangle <int> bounds = getLocalBounds();
    bounds = moduleInternalsBounds ( bounds, 
                                     MODULE_INSIDE_OFFSET, 
                                     OFFSET, 
                                     THICKNESS);

    grid.performLayout ( bounds );
}
