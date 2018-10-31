/*
  ==============================================================================

    EnvFilterModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"


// ENV FILTER
class EnvFilterModule : public CustomComponent
{
public:
    EnvFilterModule ( Slider* as, Slider* ds, 
                      Slider* ss, Slider* rs,
                      Slider* ck, Slider* rk,
                      ComboBox *fB );

    ~EnvFilterModule();
    
    void paint (Graphics& g) override;
    
    void resized () override;
    
    
    class LeftSide : public CustomComponent
    {
    public:
        LeftSide( Slider* ck, Slider* rk, ComboBox *fB);
        ~LeftSide();

        void paint (Graphics& g) override;        
        void resized () override;

    private:
        Slider* CutoffKnob;
        Slider* ResonanceKnob;
        ComboBox *FilterBox;
        
        Label FilterTypeLabel;
        Label CutoffLabel;
        Label ResonanceLabel;
    };

private:            
    Slider* AttackSlider;
    Slider* DecaySlider;
    Slider* SustainSlider;
    Slider* ReleaseSlider;

    Label AttackSliderLabel;
    Label DecaySliderLabel;
    Label SustainSliderLabel;
    Label ReleaseSliderLabel;

    LeftSide* LeftPanel;
};

