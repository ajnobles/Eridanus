/*
  ==============================================================================

    OutputModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "OutputModule.h"


OutputModule::OutputModule() 
{
    //
    
    addAndMakeVisible ( OutputSlider );
    OutputSlider.setRange ( 0, 100 );
    OutputSlider.setSliderStyle (Slider::LinearVertical);
    OutputSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 40, 20);
}


OutputModule::~OutputModule() 
{
    //
}


void OutputModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR);

    CustomComponent::buildModuleBorder( g, CORNERSIZE, THICKNESS, OFFSET );
    // TEMP IDENTIFICATION TEXT
    g.drawText ("OUTPUT", 0, 0, getWidth(), getHeight(), Justification::centred); 

}



void OutputModule::resized ()
{

    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = { Track (1_fr) };
    grid.templateColumns = { Track (1_fr) , Track (1_fr) };

    grid.items = {
        GridItem ( OutputSlider ),
        GridItem ( nullptr )
    };

    Rectangle<int> bounds = getLocalBounds();

    // printf ( "BEFORE: (%i, %i), (%i, %i)\n", bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight() );

    float change = ( THICKNESS + OFFSET ) * 1.75;
    bounds.setX( bounds.getX() + change );
    bounds.setY( bounds.getY() + change );
    bounds.setWidth ( bounds.getWidth()  - ( change * 2.0 ) );
    bounds.setHeight( bounds.getHeight() - ( change * 2.0 ) );

    // printf ( "AFTER: (%i, %i), (%i, %i)\n", bounds.getX(), bounds.getY(), bounds.getWidth(), bounds.getHeight() );

    grid.performLayout ( bounds );
}
