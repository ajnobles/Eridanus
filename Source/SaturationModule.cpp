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
    DriveKnob.setRange ( 0.0f, 1.0f );
    DriveKnob.setSliderStyle ( Slider::RotaryVerticalDrag );
    DriveKnob.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

    addAndMakeVisible( DriveLabel );
    DriveLabel.setText( "Drive", dontSendNotification );
    
    addAndMakeVisible ( TapeButton );
    TapeButton.setButtonText ( "TP" );

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
        GridItem ( DriveKnob ),
        GridItem ( DriveLabel )
    };

    Rectangle <int> bounds = getLocalBounds();

    bounds = moduleInternalsBounds ( bounds,
                                     MODULE_INSIDE_OFFSET,
                                     OFFSET,
                                     THICKNESS);


    grid.performLayout ( bounds );
}

void SaturationModule::buttonUpdate( String text )
{    
    if (text == "TP")
        saturationType = 1;

    else if (text  == "TB")
        saturationType = 2;
}

int SaturationModule::getSaturationType()
{    
    return saturationType;
}

TextButton& SaturationModule::getTapeButton()
{
    return TapeButton;
}

TextButton& SaturationModule::getTubeButton()
{
    return TubeButton;
}

bool SaturationModule::isDriveSlider ( Slider* slider )
{
    return slider == &DriveKnob;
}

float SaturationModule::getDriveSliderValue ()
{
    return DriveKnob.getValue();
}

void SaturationModule::setDriveSliderValue ( float v )
{
    DriveKnob.setValue( v );
}
