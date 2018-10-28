/*
  ==============================================================================

    LFOModule.h
    Created: 26 Oct 2018 8:29:19am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"

// LFO
class LfoModule : public CustomComponent
{
public:
    LfoModule (Slider* rs, Slider* ds, Label* rl, Label* dl); 
    ~LfoModule () {};
    void paint (Graphics& g) override;    
    void resized () override;

    bool isRateSlider(Slider* slider);
    bool isDepthSlider(Slider* slider);
    
    // GET
    // Slider* getRateSlider();
    // Slider* getDepthSlider();
    
    // SET
    

private:
    Slider* RateSlider;
    Slider* DepthSlider;
    
    Label*  RateLabel;
    Label*  DepthLabel;
};
 
