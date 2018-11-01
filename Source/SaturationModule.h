/*
  ==============================================================================

    SaturationModule.h
    Created: 26 Oct 2018 8:35:48am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"

// SATURATION
class SaturationModule : public CustomComponent
{
public:
    SaturationModule ();                       
    ~SaturationModule();
                  
    void paint (Graphics& g) override;
    void resized () override;
    
private:    
    Slider DriveKnob;
    
    TextButton TapeButton;
    TextButton TubeButton;
};
