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
	OscillatorModule (Slider* ls, ComboBox *lB, Slider* fts,  Slider* fs, ComboBox *oB);
	~OscillatorModule ();

    void paint (Graphics& g) override;
    void resized () override;
    
private:
    Slider* levelSlider;
    Slider* freqSlider;
    Slider* fineTuneSlider;
    Label levelLabel;
    Label freqLabel;
    Label fineTune;
    Label oscType;
    Label oscLength;
    ComboBox* oscBox;
    ComboBox* lengthBox;
};
