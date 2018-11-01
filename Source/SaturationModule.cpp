/*
  ==============================================================================

    SaturationModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "SaturationModule.h"

SaturationModule::SaturationModule ( )
{
    //
    addAndMakeVisible ( DriveKnob );
    DriveKnob.setRange ( 0, 100 );
    DriveKnob.setSliderStyle ( Slider::Rotary );
    DriveKnob.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

    addAndMakeVisible ( TapeButton );
    TapeButton.setButtonText ( "TB" );

    addAndMakeVisible ( TubeButton );
    TubeButton.setButtonText ( "TB" );
}

SaturationModule::~SaturationModule ( )
{
}
              
void SaturationModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR);

    buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );
    // TEMP IDENTIFICATION TEXT
    g.drawText ("SATURATION", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

}

void SaturationModule::resized ()
{
    // 
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = {
        Track (1_fr),
        Track (1_fr),
        Track (1_fr),
        Track (2_fr),
    };
    
    grid.templateColumns = { Track (1_fr) };

    grid.items = {
        GridItem (nullptr),
        GridItem ( TapeButton ),
        GridItem ( TubeButton ),
        GridItem ( DriveKnob )
    };

    Rectangle <int> bounds = getLocalBounds();

    bounds = moduleInternalsBounds ( bounds,
                                     MODULE_INSIDE_OFFSET,
                                     OFFSET,
                                     THICKNESS);


    grid.performLayout ( bounds );
}
