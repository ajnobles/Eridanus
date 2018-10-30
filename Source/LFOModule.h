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

    // LfoModule (Slider* rs, Slider* ds, String* lfoName); 

    LfoModule (); 
    ~LfoModule () {};
    void paint (Graphics& g) override;    
    void resized () override;

    bool isRateSlider(Slider* slider);
    bool isDepthSlider(Slider* slider);
    
    // GET
    float getDepthSliderValue();
    float getRateSliderValue();

    // SET
    void setDepthSliderValue( float v );
    void setRateSliderValue( float v );

   

private:
    Slider RateSlider;
    Slider DepthSlider;
    

    // String* lfoType;
    
    // Label RateLabel;
    // Label DepthLabel;

    String lfoType;
    
    Label  RateLabel;
    Label  DepthLabel;

};
 
