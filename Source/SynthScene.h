/*
  ==============================================================================

    SynthScene.h
    Created: 12 Oct 2018 11:28:14am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
// #include "SynthModulesScene.h"
// #include "SynthTitleScene.h"
#include "Utilities.h"

#include "CustomComponent.h"


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
    
    
    
    
    

private:
    SynthModulesScene ModulesScene;
    SynthTitleScene TitleScene;
    GUIUtilities Utilities;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthScene)
};
