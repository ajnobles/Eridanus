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
                        public Button::Listener,
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
        //osc 1 level
        if ( OSC_1->isLevelSlider( slider ) )
        {
            OSC_1->setLevelSliderValue( OSC_1->getLevelSliderValue() );
        }
        
        //osc 1 frequency
        else if ( OSC_1->isFreqSlider( slider ) )
        {
            OSC_1->setFreqSliderValue( OSC_1->getFreqSliderValue() );
        }
        
        //osc 1 frequency fine tune
        else if ( OSC_1->isFineTuneSlider( slider ) )
        {
            OSC_1->setFineTuneSliderValue( OSC_1->getFineTuneSliderValue() );
        }
        
        //osc 2 level
        else if ( OSC_2->isLevelSlider( slider ) )
        {
            OSC_2->setLevelSliderValue( OSC_2->getLevelSliderValue() );
        }
        
        //osc 2 frequency
        else if ( OSC_2->isFreqSlider( slider ) )
        {
            OSC_2->setFreqSliderValue( OSC_2->getFreqSliderValue() );
        }
        
        //osc 2 frequency fine tune
        else if ( OSC_2->isFineTuneSlider( slider ) )
        {
            OSC_2->setFineTuneSliderValue( OSC_2->getFineTuneSliderValue() );
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
 
        else if ( saturation->isDriveSlider( slider ) )
        {
            saturation->setDriveSliderValue( saturation->getDriveSliderValue() );
        }
        
        else if ( output->isOutputSlider( slider ) )
        {
            output->setOutputSliderValue( output->getOutputSliderValue() );
        }
    }
  
    //function handles slider changes to osc and lfo frequencies
    void updateOscOneFrequency();
    void updateOscTwoFrequency();
    void updateLFOAmpFrequency();
    void updateLFOFreqFrequency();

    //create wavetables for osc and lfo's
    void createWavetables();
    
    //function handles user selected filter type adjustments
    void comboBoxChanged(ComboBox*) override;
    
    //function handles saturation selection
    void buttonClicked(Button*) override;
    
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
    

    // OSCILLATOR 1 & 2
    OscillatorModule* OSC_1;
    OscillatorModule* OSC_2;

          
    // LFO AMP
    LfoModule* LfoAmp;
    String lfoAmp = "AMP LFO";
    

    // AMP FILTER
    AmpFilterModule* ampFilter;
  

    // ENV FILTER
    EnvFilterModule* envFilter;


    // SATURATION MODULE
    SaturationModule* saturation;
    int saturationType;
   

    // OUTPUT MODULE
    OutputModule *output;

    // KEYBOARD SCENE
    KeyboardScene *keyboard;


    //holds audio device's sample rate for osc, lfo, and filter settings
    float globalSampleRate;  
 
    double oscTableSize;    //size of wavetables (osc Arrays)

    double oscOneFrequency;    //osc frequency 
    double oscOnePhase;        //position within the osc wavetable cycle
    double oscOneIncrement;    //holds "next" place in wavetable for grabbing values
    
    double oscTwoFrequency;    //osc frequency 
    double oscTwoPhase;        //position within the osc wavetable cycle
    double oscTwoIncrement;    //holds "next" place in wavetable for grabbing values
       
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
   
    //hold oscillators' wavetables for reading/output
    Array<float> wavetableOne;
    Array<float> wavetableTwo;
    
    //Filter creation...
    //Converts mono processor into multi-channels (2), as opposed to processing independently (L and R)
    //Comprised of two components: the filter (1rst part: contains mono processor)
    //and the filter's parameters (2nd part: state types (parameters)
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, 
         dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;
 
    //handles the smoothing of fader values -> linear increments to target slider value
    LinearSmoothedValue<float> smoothOscOneOutput;
    LinearSmoothedValue<float> smoothOscTwoOutput;        
    LinearSmoothedValue<float> smoothLFOAmpDepth;
    LinearSmoothedValue<float> smoothDrive;
    LinearSmoothedValue<float> smoothOutput;
         
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
