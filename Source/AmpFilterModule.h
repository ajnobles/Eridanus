/*
  ==============================================================================

    AmpFilterModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"

class AmpFilterModule : public CustomComponent
{
public:
	AmpFilterModule ( Slider* as, Slider* ds, Slider* ss, Slider* rs,
		              Label*  al, Label*  dl, Label*  sl, Label*  rl)
		            : AttackSlider (as), DecaySlider (ds), 
		              SustainSlider (ss), ReleaseSlider (rs),
		              AttackSliderLabel (al), DecaySliderLabel (dl),
		              SustainSliderLabel (sl), ReleaseSliderLabel (rl)
	{
		addAndMakeVisible ( AttackSlider );
		AttackSlider->setRange ( 0, 100 );
		AttackSlider->setSliderStyle ( Slider::LinearVertical );
		AttackSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

		addAndMakeVisible ( DecaySlider );
		DecaySlider->setRange ( 0, 100 );
		DecaySlider->setSliderStyle ( Slider::LinearVertical );
		DecaySlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

		addAndMakeVisible ( SustainSlider );
		SustainSlider->setRange ( 0, 100 );
		SustainSlider->setSliderStyle ( Slider::LinearVertical );
		SustainSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

		addAndMakeVisible ( ReleaseSlider );
		ReleaseSlider->setRange ( 0, 100 );
		ReleaseSlider->setSliderStyle ( Slider::LinearVertical );
		ReleaseSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
	}

	void paint (Graphics& g) override
	{
		g.setColour (BORDER_COLOR);
		buildModuleBorder (g, CORNERSIZE, THICKNESS, OFFSET);

		// TEMP IDENTIFICATION TEXT
		g.drawText ("AmpFILTER", 0, 25, getWidth(), getHeight(), Justification::centredTop); 
	}

	void resized () override
	{
		// 
		Grid grid;

		using Track = Grid::TrackInfo;

		grid.templateRows = { Track (1_fr), Track (10_fr) };
		grid.templateColumns = { Track (1_fr), Track (1_fr), Track (1_fr), Track (1_fr) };

		grid.items = {
		    GridItem ( nullptr ),
		    GridItem ( nullptr ),
		    GridItem ( nullptr ),
		    GridItem ( nullptr ),
		    GridItem ( AttackSlider  ),
		    GridItem ( DecaySlider   ),
		    GridItem ( SustainSlider ),
		    GridItem ( ReleaseSlider )
		};

		Rectangle <int> bounds = getLocalBounds();
		bounds = moduleInternalsBounds ( bounds,
		                                 MODULE_INSIDE_OFFSET,
		                                 OFFSET,
		                                 THICKNESS);

		grid.performLayout ( bounds );
	}

private:
	Slider* AttackSlider;
	Slider* DecaySlider;
	Slider* SustainSlider;
	Slider* ReleaseSlider;

	Label* AttackSliderLabel;
	Label* DecaySliderLabel;
	Label* SustainSliderLabel;
	Label* ReleaseSliderLabel;
};
