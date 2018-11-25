/*
  ==============================================================================

    AmpFilterModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "AmpFilterModule.h"


AmpFilterModule::AmpFilterModule ( )
{
	addAndMakeVisible ( AttackSlider );
	AttackSlider.setRange ( 0.0f, 5.0f );
	AttackSlider.setSliderStyle ( Slider::LinearVertical );
	AttackSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

    addAndMakeVisible ( DecaySlider );
	DecaySlider.setRange ( 0.0f, 3.0f );
	DecaySlider.setSliderStyle ( Slider::LinearVertical );
	DecaySlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

	addAndMakeVisible ( SustainSlider );
	SustainSlider.setRange ( 0.0f, 1.0f );
	SustainSlider.setSliderStyle ( Slider::LinearVertical );
	SustainSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
    SustainSlider.setValue( 1.0f );

	addAndMakeVisible ( ReleaseSlider );
	ReleaseSlider.setRange ( 0.0f, 5.0f );
	ReleaseSlider.setSliderStyle ( Slider::LinearVertical );
	ReleaseSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
	
	addAndMakeVisible ( AttackSliderLabel );
    AttackSliderLabel.setText("A", dontSendNotification);
    AttackSliderLabel.setJustificationType ( Justification::centred );

    addAndMakeVisible ( DecaySliderLabel );
    DecaySliderLabel.setText("D", dontSendNotification);
    DecaySliderLabel.setJustificationType ( Justification::centred );

    addAndMakeVisible ( SustainSliderLabel );
    SustainSliderLabel.setText("S", dontSendNotification);
    SustainSliderLabel.setJustificationType ( Justification::centred );
            
    addAndMakeVisible ( ReleaseSliderLabel );
    ReleaseSliderLabel.setText("R", dontSendNotification);
    ReleaseSliderLabel.setJustificationType ( Justification::centred );

}

AmpFilterModule::~AmpFilterModule ()
{
}

void AmpFilterModule::paint (Graphics& g) 
{
	g.setColour (BORDER_COLOR);
	buildModuleBorder (g, CORNERSIZE, THICKNESS, OFFSET);

	// TEMP IDENTIFICATION TEXT
	g.drawText ("AMP ENVELOPE", 0, 25, getWidth(), getHeight(), Justification::centredTop); 
}

void AmpFilterModule::resized () 
{
	// 
	Grid grid;

	using Track = Grid::TrackInfo;

	grid.templateRows = { 
        Track (1_fr),
        Track (10_fr),  
        Track (1_fr) 
    };

	grid.templateColumns = { 
        Track (1_fr), 
        Track (1_fr), 
        Track (1_fr), 
        Track (1_fr) 
    };

	grid.items = {
	    GridItem ( nullptr  ),
	    GridItem ( nullptr  ),
	    GridItem ( nullptr  ),
	    GridItem ( nullptr  ),
	    GridItem ( AttackSlider  ),
	    GridItem ( DecaySlider   ),
	    GridItem ( SustainSlider ),
	    GridItem ( ReleaseSlider ),
	    GridItem ( AttackSliderLabel ),
        GridItem ( DecaySliderLabel ),
        GridItem ( SustainSliderLabel ),
        GridItem ( ReleaseSliderLabel )
	};

	Rectangle <int> bounds = getLocalBounds();
	bounds = moduleInternalsBounds ( bounds,
	                                 MODULE_INSIDE_OFFSET,
	                                 OFFSET,
	                                 THICKNESS);

	grid.performLayout ( bounds );
}

float AmpFilterModule::getAttackSliderValue ()
{
    return AttackSlider.getValue();
}

float AmpFilterModule::getDecaySliderValue ()
{
    return DecaySlider.getValue();
}

float AmpFilterModule::getSustainSliderValue ()
{
    return SustainSlider.getValue();
}

float AmpFilterModule::getReleaseSliderValue ()
{
    return ReleaseSlider.getValue();
}











