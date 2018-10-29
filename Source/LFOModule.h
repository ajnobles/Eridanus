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
    LfoModule (Slider* rs, Slider* ds, String* lfoName); 
    ~LfoModule () {};
    void paint (Graphics& g) override;    
    void resized () override;
    
private:
    Slider* RateSlider;
    Slider* DepthSlider;
    
    String* lfoType;
    
    Label RateLabel;
    Label DepthLabel;
};
 
