/*
  ==============================================================================

    SynthModulesScene.h
    Created: 12 Oct 2018 11:28:14am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "CustomComponent.h"

#include "OutputModule.h"
#include "InputModule.h"
#include "AmpFilterModule.h"
#include "EnvFilterModule.h"
#include "LFOModule.h"
#include "OscillatorModule.h"
#include "SaturationModule.h"


//==============================================================================
/*
*/
class SynthModulesScene    : public CustomComponent
{
public:
    SynthModulesScene();
    ~SynthModulesScene();

    void paint (Graphics&) override;
    void resized() override;

private:
    OutputModule Output;
    InputModule Input;
    AmpFilterModule AmpFilter;
    EnvFilterModule EnvFilter;
    LFOModule LFO_Freq;
    LFOModule LFO_Amp;
    OscillatorModule Oscillator;
    SaturationModule Saturation;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthModulesScene)
};
