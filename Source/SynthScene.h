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
// #include "Utilities.h"

#include "CustomComponent.h"
#include "OutputModule.h"
#include "InputModule.h"
#include "AmpFilterModule.h"
#include "EnvFilterModule.h"
// #include "LFOModule.h"
// #include "OscillatorModule.h"
// #include "SaturationModule.h"

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

    //==============================================================================
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
    
    //==============================================================================
    class SynthModulesScene    : public CustomComponent
    {
    public:
        SynthModulesScene();
        ~SynthModulesScene();

        void paint (Graphics&) override;
        void resized() override;
        
        //==============================================================================
        class SaturationModule : public CustomComponent
        {
        public:
            SaturationModule();
            ~SaturationModule();

            void paint (Graphics& g) override;
            void resized () override;

        private:
            Slider DriveKnob;
            TextButton TapeButton;
            TextButton TubeButton;

            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SaturationModule)
        };
        
        //==============================================================================
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

        //==============================================================================
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
        //==============================================================================
    
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

    //==============================================================================
    class GUIUtilities    : public CustomComponent
    {
    public:
        GUIUtilities();
        ~GUIUtilities();

        void paint (Graphics&) override;
        void resized() override;


        class Selectors : public CustomComponent
        {
        public:
            Selectors();
            ~Selectors();
            void paint (Graphics&) override;
            void resized () override;
        private:
            JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Selectors);
        };

        

    
    
    //==============================================================================

    
    
    
    //==============================================================================
        
        
private:

    Selectors Presets;
    Selectors MidiChannel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIUtilities)
};
    
    

private:
    SynthModulesScene ModulesScene;
    SynthTitleScene TitleScene;
    GUIUtilities Utilities;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SynthScene)
};
