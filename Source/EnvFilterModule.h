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


class EnvFilterModule : public CustomComponent
{
public:
    EnvFilterModule();
    ~EnvFilterModule();

    void paint (Graphics& g) override;
    void resized () override;

    class LeftSide : public CustomComponent
    {
    public:
        LeftSide::LeftSide();
        LeftSide::~LeftSide();

        void paint (Graphics& g) override;
        void resized () override;
    private:
        Slider CutoffKnob;
        Slider ResonanceKnob;

        TextButton HighPassButton;
        TextButton LowPassButton;
        TextButton BandPassButton;

    };

private:
    Slider AttackSlider;
    Slider DecaySlider;
    Slider SustainSlider;
    Slider ReleaseSlider;

    LeftSide LeftPanel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EnvFilterModule)
};
