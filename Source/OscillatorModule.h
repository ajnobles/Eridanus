/*
  ==============================================================================

    OscillatorModule.h
    Created: 26 Oct 2018 7:59:28am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"


enum LengthState 
{
    ZERO,
    FOUR,
    EIGHT,
    SIXTEEN
};

enum WaveState 
{
    SIN,
    SAW,
    TRIANGLE,
    SQUARE
};


class OscillatorModule : public CustomComponent// ,
                         // public ComboBox::Listener
{
public:
	OscillatorModule ( );
	~OscillatorModule ();

    void paint (Graphics& g) override;
    void resized () override;

    void comboBoxUpdate ( String text );

    void lengthButtonClicked ( Button* current );
    void waveButtonClicked ( Button* current );
    

    void changeWaveState (WaveState newWave);
    void changeLengthState (LengthState newLength);    

    bool isLevelSlider( Slider* slider );
    bool isFreqSlider( Slider* slider );
    bool isFineTuneSlider( Slider* slider );
    bool isLength0Button( Button *button);
    bool isLength4Button( Button *button);
    bool isLength8Button( Button *button);
    bool isLength16Button( Button *button);
    bool isSinWaveButton( Button *button );
    bool isSawWaveButton( Button *button );
    bool isTriangleWaveButton( Button *button );
    bool isSquareWaveButton( Button *button );
    bool isThis ( Button *button );

    float getLevelSliderValue();
    float getFreqSliderValue();
    float getFineTuneSliderValue();
    float getOscMult();

    ComboBox& getOscBox();
    ComboBox& getLengthBox();

    TextButton& getLength0Button();
    TextButton& getLength4Button();
    TextButton& getLength8Button();
    TextButton& getLength16Button();

    TextButton& getSinButton();
    TextButton& getSawButton();
    TextButton& getTriangleButton();
    TextButton& getSquareButton();

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

    TextButton length0;
    TextButton length4;
    TextButton length8;
    TextButton length16;
    LengthState lenState;

    TextButton sinButton;
    TextButton sawButton;
    TextButton triButton;
    TextButton sqrButton;
    WaveState waveState;
    

    ComboBox oscBox;
    ComboBox lengthBox;

    float oscMult;

    String oscType;
};
