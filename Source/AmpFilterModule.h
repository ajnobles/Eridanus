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
	AmpFilterModule ( Slider* as, Slider* ds, Slider* ss, Slider* rs);
    ~AmpFilterModule ();
	
    void paint (Graphics& g) override;
	void resized () override;
  
private:
	Slider* AttackSlider;
	Slider* DecaySlider;
	Slider* SustainSlider;
	Slider* ReleaseSlider;

	Label AttackSliderLabel;
	Label DecaySliderLabel;
	Label SustainSliderLabel;
	Label ReleaseSliderLabel;
};
