/*
  ==============================================================================

    OscillatorModule.h
    Created: 26 Oct 2018 7:59:28am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"
// #include "MainComponent.h"

class OscillatorModule : public CustomComponent// ,
                         // public ComboBox::Listener
{
public:
	OscillatorModule ( );
	~OscillatorModule ();

    void paint (Graphics& g) override;
    void resized () override;

    void comboBoxUpdate ( String text );
    // void comboBoxChanged ( ComboBox* box ) override;

    bool isLevelSlider( Slider* slider );
    bool isFreqSlider( Slider* slider );
    bool isFineTuneSlider( Slider* slider );

    float getLevelSliderValue();
    float getFreqSliderValue();
    float getFineTuneSliderValue();
    float getOscMult();
    ComboBox& getOscBox();
    ComboBox& getLengthBox();
    String getOscType();

    void setLevelSliderValue( float v );
    void setFreqSliderValue( float v );
    void setFineTuneSliderValue( float v );
    void setOscMult( float v );
    
    
private:
    Slider levelSlider;
    Slider freqSlider;
    Slider fineTuneSlider;

    Label levelLabel;
    Label freqLabel;
    Label fineTune;
    Label oscTypeLabel;
    Label oscLength;

    TextButton length4;
    TextButton length8;
    TextButton length16;

    TextButton sin;
    TextButton saw;
    TextButton tri;
    TextButton sqr;
    

    ComboBox oscBox;
    ComboBox lengthBox;

    float oscMult;

    String oscType;
};
