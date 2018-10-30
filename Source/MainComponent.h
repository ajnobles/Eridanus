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
        
// <<<<<<< Integration_10_29_18
        //osc frequency fine tune
        else if (slider == &fineTuneSlider)
        {
            fineTuneSlider.setValue(fineTuneSlider.getValue());
        }
        
        //amp lfo rate (freq)
        // else if (slider == &lfoAmpRateSlider)
// =======
        //lfo rate (freq)
        else if ( LfoAmp->isRateSlider( slider ) ) 
// >>>>>>> Allen_Gui_Main
        {
            LfoAmp->setRateSliderValue( LfoAmp->getRateSliderValue() );
        }
        
// <<<<<<< Integration_10_29_18
        //amp lfo depth
        // else if (slider == &lfoAmpDepthSlider)
// =======
        //lfo depth
        else if ( LfoAmp->isDepthSlider( slider ) )
// >>>>>>> Allen_Gui_Main
        {
            LfoAmp->setDepthSliderValue( LfoAmp->getDepthSliderValue() );
        }
        
        //fm lfo rate (freq)
        else if (slider == &lfoFreqRateSlider)
        {
            lfoFreqRateSlider.setValue(lfoFreqRateSlider.getValue());
        }
        
        //fm lfo depth
        else if (slider == &lfoFreqDepthSlider)
        {
            lfoFreqDepthSlider.setValue(lfoFreqDepthSlider.getValue());
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
    
// <<<<<<< Integration_10_29_18
    // LFO FREQ MODULE
    /*
    Slider lfoFreqRateSlider;
    Slider lfoFreqDepthSlider;
    
    Label  lfoFreqRateLabel;
    Label  lfoFreqDepthLabel;
    */  

    String lfoFM = "FM LFO";
    // OSC MODULE
// =======

    // INPUT MODULE
    InputModule* Input;
    

    // LFO FREQ MODULE
    LfoModule* LfoFreq;
    

    //sliders for osc and filter controls
// >>>>>>> Allen_Gui_Main
    Slider oscLevelSlider;
    Slider freqSlider;
    Slider fineTuneSlider;
    
    ComboBox oscBox;   
    String oscType;
// <<<<<<< Integration_10_29_18
    
    ComboBox lengthBox;
    String lengthType;
    double oscMult;
           
    // LFO AMP
    /*  
    Slider lfoAmpRateSlider;
    Slider lfoAmpDepthSlider;
    
    Label lfoAmpRateLabel;
    Label lfoAmpDepthLabel;
    */
    String lfoAmp = "AMP LFO";
    
    // ENV AMP
// =======
   

    // LFO AMP
    LfoModule* LfoAmp;
       
    // ENV FILTER
// >>>>>>> Allen_Gui_Main
    Slider envAttackSlider;
    Slider envDecaySlider;
    Slider envSustainSlider;
    Slider envReleaseSlider;
    
    // ENV FILTER
    Slider ampAttackSlider;
    Slider ampDecaySlider;
    Slider ampSustainSlider;
    Slider ampReleaseSlider;
    Slider cutoffSlider;
    Slider resonanceSlider;
    
    ComboBox filterBox;
    String filterType;      
    
    // SATURATION MODULE
    Slider satDriveKnob;
    
    TextButton satTubeButton;
    TextButton satTapeButton; 
    
    // OUTPUT MODULE
    Slider outputLevelSlider;
    Slider outputFeedbackSlider;
    
    Label outputLevelLabel;
// <<<<<<< Integration_10_29_18
    // Label outputFeedbackLabel;      
// =======
    Label outputFeedbackLabel;
    

    //combo boxes osc and filter types
    ComboBox filterBox;     


    //strings hold osc and filter selections
    String filterType;      
    
    Slider cutoffSlider;
    Slider resonanceSlider;
    
    Label cutoffLabel;
    Label resonanceLabel;
// >>>>>>> Allen_Gui_Main
    
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
