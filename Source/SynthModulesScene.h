/*
  ==============================================================================

    SynthModulesScene.h
    Created: 12 Oct 2018 11:28:14am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SynthModulesScene    : public Component
{
public:
    SynthModulesScene();
    ~SynthModulesScene();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthModulesScene)
};
