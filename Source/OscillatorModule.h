/*
  ==============================================================================

    OscillatorModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"


class OscillatorModule : public CustomComponent
{
public:
    OscillatorModule();
    ~OscillatorModule();

    void paint (Graphics& g) override;
    void resized () override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscillatorModule)
};
