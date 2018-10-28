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
        if (slider == &oscLevelSlider)
        {
            oscLevelSlider.setValue(oscLevelSlider.getValue());
        }
        
        //osc frequency
        else if (slider == &freqSlider)
        {
            freqSlider.setValue(freqSlider.getValue());
        }
        
        //lfo rate (freq)
        else if ( // (slider == &lfoAmpRateSlider)
        {
            lfoAmpRateSlider.setValue(lfoAmpRateSlider.getValue());
        }
        
        //lfo depth
        else if (slider == &lfoAmpDepthSlider)
        {
            lfoAmpDepthSlider.setValue(lfoAmpDepthSlider.getValue());
        }
    }
  
    //function handles slider changes to osc and lfo frequencies
    void updateOscFrequency();
    void updateLFOAmpFrequency();

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
    // Slider InputLevelSlider;
    // Label  InputLevelSliderLabel;
    
    // LFO FREQ MODULE
    Slider lfoFreqRateSlider;
    Slider lfoFreqDepthSlider;
    
    Label  lfoFreqRateLabel;
    Label  lfoFreqDepthLabel;
    
    
    //sliders for osc and filter controls
    Slider oscLevelSlider;
    Slider freqSlider;
    
    Label oscLevelLabel;
    Label freqLabel;
    
    ComboBox oscBox;  
    
    String oscType;
           
    // LFO AMP
    
    Slider lfoAmpRateSlider;
    Slider lfoAmpDepthSlider;
    Label lfoAmpRateLabel;
    Label lfoAmpDepthLabel;
    
    // ENV FILTER
    Slider envAttackSlider;
    Slider envDecaySlider;
    Slider envSustainSlider;
    Slider envReleaseSlider;
    
    Label envAttackLabel;
    Label envDecayLabel;
    Label envSustainLabel;
    Label envReleaseLabel;
    
    // AMP FILTER
    Slider ampAttackSlider;
    Slider ampDecaySlider;
    Slider ampSustainSlider;
    Slider ampReleaseSlider;
    Slider ampCutoffKnob;
    Slider ampResonanceKnob;
    
    TextButton ampHighPassButton;
    TextButton ampLowPassButton;
    TextButton ampBandPassButton;    
    
    Label ampAttackLabel;
    Label ampDecayLabel;
    Label ampSustainLabel;
    Label ampReleaseLabel;
    
    // SATURATION MODULE
    Slider satDriveKnob;
    
    TextButton satTubeButton;
    TextButton satTapeButton; 
    
    // OUTPUT MODULE
    Slider outputLevelSlider;
    Slider outputFeedbackSlider;
    
    Label outputLevelLabel;
    Label outputFeedbackLabel;
    

    //combo boxes osc and filter types
    ComboBox filterBox;     


    //strings hold osc and filter selections
    String filterType;      

    
    Slider cutoffSlider;
    Slider resonanceSlider;
    
    Label cutoffLabel;
    Label resonanceLabel;
    
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
    
    //data structure (JUCE's array class, similar to vector) holds osc wavetables
    Array<float> sineTable;
    Array<float> squareTable;
    Array<float> sawTable;
    Array<float> triangleTable;
    Array<float> lfoAmpTable;
    
    //Filter creation...
    //Converts mono processor into multi-channels (2), as opposed to processing independently (L and R)
    //Comprised of two components: the filter (1rst part: contains mono processor)
    //and the filter's parameters (2nd part: state types (parameters)
    dsp::ProcessorDuplicator<dsp::StateVariableFilter::Filter<float>, 
         dsp::StateVariableFilter::Parameters<float>> stateVariableFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
