/*
  ==============================================================================

    EnvFilterModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"


// ENV FILTER
class EnvFilterModule : public CustomComponent
{
public:
    EnvFilterModule ( Slider* as, Slider* ds, 
                      Slider* ss, Slider* rs,
                      Slider* ck, Slider* rk,
                      TextButton* hpb,
                      TextButton* lpb,
                      TextButton* bpb,
                      Label*  al, Label*  dl, 
                      Label*  sl, Label*  rl );

    ~EnvFilterModule ();
    void paint (Graphics& g) override;
    void resized () override;
    
    
    class LeftSide : public CustomComponent
    {
    public:
        LeftSide( Slider* ck, Slider* rk, TextButton* hpb, TextButton* lpb, TextButton* bpb);
        void paint (Graphics& g) override;
        void resized () override;
    private:
        Slider* CutoffKnob;
        Slider* ResonanceKnob;

        TextButton* HighPassButton;
        TextButton* LowPassButton;
        TextButton* BandPassButton;
    };

private:            
    Slider* AttackSlider;
    Slider* DecaySlider;
    Slider* SustainSlider;
    Slider* ReleaseSlider;

    Label* AttackSliderLabel;
    Label* DecaySliderLabel;
    Label* SustainSliderLabel;
    Label* ReleaseSliderLabel;

    LeftSide* LeftPanel;
};

