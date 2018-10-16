/*
  ==============================================================================

    SynthScene.h
    Created: 12 Oct 2018 11:28:14am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthModulesScene.h"
#include "SynthTitleScene.h"
#include "Utilities.h"


//==============================================================================
/*
*/
class SynthScene    : public Component
{
public:
    SynthScene();
    ~SynthScene();

    void paint (Graphics&) override;
    void resized() override;

private:
    SynthModulesScene ModulesScene;
    SynthTitleScene TitleScene;
    GUIUtilities Utilities;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthScene)
};
