/*
  ==============================================================================

    LFOModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "LFOModule.h"

LfoModule::LfoModule (Slider* rs)
    : RateSlider (rs)
{
    
    addAndMakeVisible ( RateSlider );
    RateSlider->setRange ( 0, 100 );
    RateSlider->setSliderStyle ( Slider::LinearVertical );
    RateSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
   

    addAndMakeVisible ( DepthSlider );
    DepthSlider.setRange ( 0, 100 );
    DepthSlider.setSliderStyle ( Slider::LinearVertical );
    DepthSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );        

}    
    
void LfoModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR);

    CustomComponent::buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

    // TEMP IDENTIFICATION TEXT
    g.drawText ("LFO", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

}

void LfoModule::resized ()
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


bool LfoModule::isRateSlider ( Slider* slider )
{
    return slider == RateSlider;
}

bool LfoModule::isDepthSlider( Slider* slider )
{
    return slider == &DepthSlider;
}



float LfoModule::getDepthSliderValue ()
{
    return DepthSlider.getValue();
}

