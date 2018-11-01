/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"

#include "KeyboardScene.h"

#include "InputModule.h"
#include "OscillatorModule.h"
#include "AmpFilterModule.h"
#include "EnvFilterModule.h"
#include "LFOModule.h"
#include "SaturationModule.h"
#include "OutputModule.h"


//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/


class MainComponent   : // public Component,
                        // public AudioSource,
                        public AudioAppComponent,
                        public Slider::Listener, 
                        private ComboBox::Listener
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    //==============================================================================
    //handles value changes in sliders
    void sliderValueChanged (Slider* slider) override
    {
        //osc level
        if ( OSC_1->isLevelSlider( slider ) )
        {
            OSC_1->setLevelSliderValue( OSC_1->getLevelSliderValue() );
        }
        
        //osc frequency
        else if ( OSC_1->isFreqSlider( slider ) )
        {
            OSC_1->setFreqSliderValue( OSC_1->getFreqSliderValue() );
        }
        
        //osc frequency fine tune
        else if ( OSC_1->isFineTuneSlider( slider ) )
        {
            OSC_1->setFineTuneSliderValue( OSC_1->getFineTuneSliderValue() );
        }
        
        //amp lfo rate (freq)
        else if ( LfoAmp->isRateSlider( slider ) ) 
        {
            LfoAmp->setRateSliderValue( LfoAmp->getRateSliderValue() );
        }
        
        else if ( LfoAmp->isDepthSlider( slider ) )
        {
            LfoAmp->setDepthSliderValue( LfoAmp->getDepthSliderValue() );
        }
    }
  
    //function handles slider changes to osc and lfo frequencies
    void updateOscFrequency();
    void updateLFOAmpFrequency();
    void updateLFOFreqFrequency();

    //create wavetables for osc and lfo's
    void createWavetables();
    
    //function handles user selected filter type adjustments
    void comboBoxChanged(ComboBox*) override;
    
    //updates changes within filter settings
    void updateFilterSettings();

   
private:
    //==============================================================================
    // Your private member variables go here...
    Random random;      //for random float number (0 - 1) generation for noise generator


    // SCENE COMPONENTS
    OwnedArray<Component> modules;
    OwnedArray<Component> scenes;
    

    // INPUT MODULE
    InputModule* Input;
    

    // LFO FREQ MODULE
    LfoModule* LfoFreq;
    String lfoFM = "FM LFO";
    

    // OSCILLATOR 1
    //sliders for osc and filter controls
    OscillatorModule* OSC_1;
          

    // LFO AMP
    LfoModule* LfoAmp;
    String lfoAmp = "AMP LFO";
    

    // AMP FILTER
    AmpFilterModule* ampFilter;
  

    // ENV FILTER
    EnvFilterModule* envFilter;


    // SATURATION MODULE
    SaturationModule* saturation;
   

    // OUTPUT MODULE
    OutputModule *output;


    //holds audio device's sample rate for osc, lfo, and filter settings
    float globalSampleRate;  
 
    double oscTableSize;    //size of wavetables (osc Arrays)
    double oscFrequency;    //osc frequency 
    double oscPhase;        //position within the osc wavetable cycle
    double oscIncrement;    //holds "next" place in wavetable for grabbing values
       
    double lfoTableSize;    //size of wavetable (lfo Array)
    double lfoFrequency;    //lfo frequency 
    double lfoPhase;        //position within the lfo wavetable cycle
    double lfoIncrement;    //position within the lfo wavetable cycle
    
    double lfoFreqTableSize;    //size of wavetable (lfo FM Array)
    double lfoFreqFrequency;    //lfo FM frequency 
    double lfoFreqPhase;        //position within the lfo FM wavetable cycle
    double lfoFreqIncrement;    //position within the lfo FM wavetable cycle
    
    //data structure (JUCE's array class, similar to vector) holds osc wavetables
    Array<float> sineTable;
    Array<float> squareTable;
    Array<float> sawTable;
    Array<float> triangleTable;
    Array<float> lfoAmpTable;
    Array<float> lfoFreqTable;
    
    //Filter creation...
    //Converts mono processor into multi-channels (2), as opposed to processing independently (L and R)
    //Comprised of two components: the filter (1rst part: contains mono processor)
    //and the filter's parameters (2nd part: state types (parameters)
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, 
         dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
