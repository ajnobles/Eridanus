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
                        private MidiInputCallback,
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
        
        //amp lfo depth
        else if ( LfoAmp->isDepthSlider( slider ) )
        {
            LfoAmp->setDepthSliderValue( LfoAmp->getDepthSliderValue() );
        }
 
        //saturation drive 
        else if ( saturation->isDriveSlider( slider ) )
        {
            saturation->setDriveSliderValue( saturation->getDriveSliderValue() );
        }
        
        //synth output
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
    
    //handle amp envelope manipulation
    void ampEnvelope();
    
    //function receives incoming MIDI messages (Midi input device & Midi message argruments)
    void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override
    {
        //convert MIDI note to frequency for OSC's
        midiFrequency = (float) MidiMessage::getMidiNoteInHertz (message.getNoteNumber());
        
        //store MIDI note velocity for OSCs' levels
        midiVelocity = message.getFloatVelocity();
        
        if (message.isNoteOn())
        {
            smoothStart = true;
            
            attackAmpEnv = true;
            decayAmpEnv = false;
            releaseAmpEnv = false;
        }
        
        if (message.isNoteOff())
        {            
            attackAmpEnv = false;
            decayAmpEnv = false;
            releaseAmpEnv = true;
        }
    };
    
    //select MIDI input device for listening
    void setMidiInputDevice (int index)
    {
        //store list (String Array) of available MIDI devices
        auto deviceList = MidiInput::getDevices();
        
        //store MIDI device (3rd option [2] for connected controller)
        auto newMidiDeviceInput = deviceList[index];

        //enable MIDI input device (controller)
        deviceManager.setMidiInputEnabled(newMidiDeviceInput, true);

        //set manager to receive all incoming events from the enabled device
        deviceManager.addMidiInputCallback(newMidiDeviceInput, this);
    }
      
private:
    //==============================================================================
    
    //Manages the state (properties) of Audio/MIDI devices
    AudioDeviceManager deviceManager;

    //Store MIDI Note On Frequency and Velocity
    float midiFrequency = 300.0f;
    float midiVelocity = 0.0f;
    
    float ampEnvValue = 0.0f;
    float envTemp = 1.0f;
    bool attackAmpEnv = false;
    bool decayAmpEnv = false;
    bool releaseAmpEnv = false;
    
    bool smoothStart = false;
    bool smoothStartFlag = false;

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


    //holds audio device's sample rate for osc, lfo, and filter settings
    float globalSampleRate;  
 
    double oscTableSize;    //size of wavetables (osc Arrays)

    double oscOneFrequency;    //osc frequency 
    double oscOnePhase;        //position within the osc wavetable cycle
    double oscOneIncrement;    //holds "next" place in wavetable for grabbing values
    
    double oscTwoFrequency;    //osc frequency 
    double oscTwoPhase;        //position within the osc wavetable cycle
    double oscTwoIncrement;    //holds "next" place in wavetable for grabbing values
       
    double lfoAmpFrequency;    //lfo Amp frequency 
    double lfoAmpPhase;        //position within the lfo Amp wavetable cycle
    double lfoAmpIncrement;    //position within the lfo Amp wavetable cycle
    
    double lfoFreqFrequency;    //lfo FM frequency 
    double lfoFreqPhase;        //position within the lfo FM wavetable cycle
    double lfoFreqIncrement;    //position within the lfo FM wavetable cycle
    
    //data structure (JUCE's array class, similar to vector) holds osc wavetables
    Array<float> sineTable;
    Array<float> squareTable;
    Array<float> sawTable;
    Array<float> triangleTable;
   
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
    LinearSmoothedValue<float> smoothOsc1Level;
    LinearSmoothedValue<float> smoothOsc2Level;
    LinearSmoothedValue<float> smoothLFOAmpDepth;
    LinearSmoothedValue<float> smoothAmpEnv;
    LinearSmoothedValue<float> smoothDrive;
    LinearSmoothedValue<float> smoothOutput;
         
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
