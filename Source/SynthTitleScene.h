/*
  ==============================================================================

    SynthTitleScene.h
    Created: 16 Oct 2018 10:54:03am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthModulesScene.h"


//==============================================================================
/*
*/
class SynthTitleScene    : public CustomComponent
{
public:
    SynthTitleScene();
    ~SynthTitleScene();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthTitleScene)
};
