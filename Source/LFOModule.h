/*
  ==============================================================================

    LFOModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"


class LFOModule : public CustomComponent
{
public:
    LFOModule();
    ~LFOModule();

    void paint (Graphics& g) override;
    void resized () override;

private:
    Slider RateSlider;
    Slider DepthSlider;

    Label RateSliderLabel;
    Label DepthSliderLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (LFOModule)
};
