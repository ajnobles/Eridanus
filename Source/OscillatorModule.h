/*
  ==============================================================================

    OscillatorModule.h
    Created: 26 Oct 2018 7:59:28am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"

class OscillatorModule : public CustomComponent
{
public:
	OscillatorModule (Slider* ls, Label* ll, Slider* fs, Label* fl, ComboBox *oB);
	~OscillatorModule ();

    void paint (Graphics& g) override;
    void resized () override;
    
private:
    Slider* levelSlider;
    Slider* freqSlider;
    Label*  levelLabel;
    Label*  freqLabel;
    ComboBox* oscBox;

};
