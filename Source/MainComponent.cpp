/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{    
    // LFO FREQ
/*    
    modules.add (new LfoModule (
        &lfoFreqRateSlider,
        &lfoFreqDepthSlider,
        &lfoFM
    ) ); 
*/

{
    // INPUT
    Input = new InputModule();
    modules.add ( Input );
    
    // LFO FREQ
    LfoFreq = new LfoModule ( );
    modules.add ( LfoFreq );
    
    // OSCILLATORS
    modules.add (new OscillatorModule ( 
        &oscLevelSlider,
        &lengthBox,
        &fineTuneSlider,
        &freqSlider, 
        &oscBox
    ) );
    
    // LFO AMP
  /*
    modules.add (new LfoModule (
        &lfoAmpRateSlider,
        &lfoAmpDepthSlider,
        &lfoAmp
    ) );
 */
    
    // LFO AMP
    LfoAmp = new LfoModule( ); 
    modules.add ( LfoAmp );
   

    // AMP FILTER
    modules.add (new AmpFilterModule ( 
        &envAttackSlider, 
        &envDecaySlider, 
        &envSustainSlider, 
        &envReleaseSlider,
        &envAttackLabel,
        &envDecayLabel,
        &envSustainLabel,
        &envReleaseLabel
    ) );
   
    // ENV FILTER
    modules.add (new EnvFilterModule ( 
        &ampAttackSlider, 
        &ampDecaySlider, 
        &ampSustainSlider, 
        &ampReleaseSlider,
        &cutoffSlider,
        &resonanceSlider,
        &filterBox
    ) );
    
    // AMP FILTER
    modules.add (new AmpFilterModule ( 
        &envAttackSlider, 
        &envDecaySlider, 
        &envSustainSlider, 
        &envReleaseSlider
    ) );
    
    // SATURATION
    modules.add ( new SaturationModule (
        &satDriveKnob,  // DRIVE KNOB
        &satTapeButton, // TAPE BUTTON
        &satTubeButton  // TUBE BUTTON
    ) );
    
    // OUTPUT
    modules.add ( new OutputModule (
        &outputLevelSlider, 
        &outputFeedbackSlider,
        &outputLevelLabel,  
        &outputFeedbackLabel 
    ) );

    int numModules = modules.size();
    for (int i = 0; i < numModules; i++) {
        addAndMakeVisible ( modules[i] );
    }

    // SCENES
    scenes.add ( new KeyboardScene );
    addAndMakeVisible ( scenes[0] );
    
    // COMPONENT LISTENERS
    oscBox.addListener(this);
    filterBox.addListener(this);
    lengthBox.addListener(this);


    //set window size
    setSize (1600, 800);
    
    //set audio channels to 0 Inputs and 2 Outputs(Stereo playback)
    setAudioChannels (0, 2);
    
// <<<<<<< Integration_10_29_18
    //set combo box selections ("8", sine, low pass)     
    lengthBox.setSelectedId(2);
    oscBox.setSelectedId(1);    
    filterBox.setSelectedId(1);  
// =======
    //set filter combo box to low pass filter
    filterBox.setSelectedId(1);
    
    //set osc combo box to sine
    oscBox.setSelectedId(1);
    
    //set sliders for osc and filter controls
    cutoffSlider.setValue(1000);
    LfoAmp->setRateSliderValue( 1.0 ); 
    LfoAmp->setDepthSliderValue( 0.0 );

// >>>>>>> Allen_Gui_Main
}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.


    shutdownAudio();
}

//prepareToPlay happens once when application is launched 
//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate) 
{        
    //grab sampleRate for filter settings
    globalSampleRate = sampleRate;   
    
    //grab osc and lfo slider frequency values 
    oscFrequency = freqSlider.getValue();

// <<<<<<< Integration_10_29_18
    // lfoFrequency = lfoAmpRateSlider.getValue();
    lfoFreqFrequency = lfoFreqRateSlider.getValue();
        
// =======
    lfoFrequency = LfoAmp->getRateSliderValue(); 

// >>>>>>> Allen_Gui_Main
    //set for starting at beginning of osc and lfo wavetables
    oscPhase = 0;
    lfoPhase = 0;
    lfoFreqPhase = 0;
    
    //set wavetable size
    oscTableSize = 1024;
    lfoTableSize = 1024;
    lfoFreqTableSize = 1024;

    //Determine increment size to find the next point in the osc wavetable for grabbing values 
    //Multiply the current osc frequency by the wavetable size, then divide by the sample rate
    //Note: initialized here, but modifiable via functions 
    oscIncrement = oscFrequency * oscTableSize / globalSampleRate;
    lfoIncrement = lfoFrequency * lfoTableSize / globalSampleRate;
    lfoFreqIncrement = lfoFreqFrequency * lfoFreqTableSize / globalSampleRate;
    
    //generate wavetables for osc and lfo's
    createWavetables();
    
    //relay settings (sample rate and block size) to dsp object (filter) 
    dsp::ProcessSpec spec;
    spec.sampleRate = globalSampleRate;
    spec.maximumBlockSize = samplesPerBlockExpected;
    
    //clear out garbage values
    stateVariableFilter.reset();    
        
    //initialize filter 
    stateVariableFilter.prepare(spec);
}


//audio-processing - AudioSouceChannel -> where to get buffer and channel information
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) 
{
    //grab osc and lfo depth slider values
    auto oscLevel = (float) oscLevelSlider.getValue();
    auto lfoDepth = (float) LfoAmp->getDepthSliderValue(); 
        
    //create pointers to beginning of both channels' buffer (for writing)
    auto* channelOne = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    auto* channelTwo = bufferToFill.buffer->getWritePointer( 1, bufferToFill.startSample);
    
    //loop with conditional statements handles osc selection (from wavetables) for writing to buffer
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
       //grab the lfo (amp) phase position
       float lfoPhasePosition = lfoAmpTable[(int)lfoPhase];
       
       //For the following osc's, grab the sample (from wavetable) in accordance to current phase 
       //Thereafter, multiply against the osc level slider to determine amplitude
       //Next, multiply the lfo (amp) with the lfo slider (depth) to determine modulation value
       //Next, multiply the prior products to determine the lfo (amp) effect to the osc sample
       //Next, multiply this original osc sample with (1 - lfo depth) to create a "dry" signal
       //Lastly, add this "wet" and "dry" together, where the lfo's depth handles the ratio between the mentioned
       if (oscType == "Triangle")
       {
           channelOne[sample] = ((triangleTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((triangleTable[(int)oscPhase] * oscLevel) * (1.0f - lfoDepth));
           channelTwo[sample] = ((triangleTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((triangleTable[(int)oscPhase] * oscLevel) * (1.0f - lfoDepth));
       }
       else if (oscType == "Square")
       {
           channelOne[sample] = ((squareTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((squareTable[(int)oscPhase] * oscLevel) * (1.0f - lfoDepth));
           channelTwo[sample] = ((squareTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((squareTable[(int)oscPhase] * oscLevel) * (1.0f - lfoDepth));
       }
       else if (oscType == "Saw")
       {
           channelOne[sample] = ((sawTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((sawTable[(int)oscPhase] * oscLevel) * (1.0f - lfoDepth));
           channelTwo[sample] = ((sawTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((sawTable[(int)oscPhase] * oscLevel) * (1.0f - lfoDepth));
       }
       else //sine
       {
           channelOne[sample] = ((sineTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((sineTable[(int)oscPhase] * oscLevel) * (1.0 - lfoDepth));
           channelTwo[sample] = ((sineTable[(int)oscPhase] * oscLevel) * (lfoDepth * lfoPhasePosition)) + 
                                ((sineTable[(int)oscPhase] * oscLevel) * (1.0 - lfoDepth));
       }
       
// <<<<<<< Integration_10_29_18
       //update osc and lfo frequencies/phases
       // updateOscFrequency();
       // updateLFOAmpFrequency();
       updateLFOFreqFrequency();
// =======
       //update osc and lfo frequencies
       updateOscFrequency( );
       updateLFOAmpFrequency( );
// >>>>>>> Allen_Gui_Main
    }
     
    //grab filled buffer and store in sample block (so we can use with the filter)
    dsp::AudioBlock<float> sampleBlock (*bufferToFill.buffer);
    
    //grab filter parameter settings
    updateFilterSettings();
    
    //process sample block (buffer) with the filter
    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (sampleBlock));
}

//When the audio device stops or restarted
void MainComponent::releaseResources() 
{    
    Logger::getCurrentLogger()->writeToLog ("Releasing resources");
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    Grid grid;
    
    using Track = Grid::TrackInfo;
        
    grid.templateRows    = {
        Track (1_fr),
        Track (1_fr),
        Track (2_fr)
    };
    
    grid.templateColumns = {
        Track (1_fr),
        Track (2_fr),
        Track (1_fr),
        Track (3_fr),
        Track (2_fr),
        Track (1_fr),
        Track (1_fr),
    };
    
/*
    grid.autoRows = Track (1_fr);
    grid.autoColumns = Track (1_fr);

    grid.autoFlow = Grid::AutoFlow::column;
*/
    /* 
    grid.templateAreas = {
        "input lfoFreq Oscillators lfoAmp envFilter ampFilter saturation output"
        "input lfoFreq Oscillators lfoAmp envFilter ampFilter saturation output",
        "input lfoFreq Oscillators lfoAmp envFilter ampFilter saturation output"
    };
     */
    
    grid.items = {
        GridItem ( modules[0] ).withArea( 1, 1, 3, 1 ),
        GridItem ( modules[1] ).withArea( 1, 2, 3, 2 ),
        GridItem ( modules[2] ).withArea( 1, 3, 2, 3 ),
        GridItem ( modules[3] ).withArea( 1, 4, 3, 4 ),
        GridItem ( modules[4] ).withArea( 1, 5, 3, 5 ),
        GridItem ( modules[5] ).withArea( 1, 6, 3, 6 ),
        GridItem ( modules[6] ).withArea( 1, 7, 3, 7 ),
        GridItem ( modules[7] ).withArea( 1, 8, 3, 8 ),
        GridItem ( scenes [0] ).withArea( 3, 1, 3, 8 )
    };

    /*
    int numModules = modules.size();
    
    for (int i = 0; i < numModules; i++) {
        grid.items.add ( modules[i] );
    }

    grid.items.add ( scenes[0] );
    */
      
    Rectangle<int> bounds = getLocalBounds();
    
    grid.performLayout ( bounds );

}

//Handles combo box changes - grab selection's text
void MainComponent::comboBoxChanged(ComboBox* box)
{
    //handles changes to filter type
    if (box->getText() == "Low Pass" || box->getText() == "Band Pass" || box->getText() == "High Pass")
    {
        filterType = box->getText();
    }

    //handles changes to osc length type
    if (box->getText() == "4" || box->getText() == "8" || box->getText() == "16")
    {
        //set osc length multiplier to appropriate value
        if (box->getText() == "4")
        {
          oscMult = 0.5;   
        }
        
        else if (box->getText() == "8")
        {
          oscMult = 1;   
        }
        
        else if (box->getText() == "16")
        {
          oscMult = 2;   
        }
    }
    
    //handles changes to osc type
    if (box->getText() == "Sine" || box->getText() == "Saw" || box->getText() == "Square" || box->getText() == "Triangle")
    {
        oscType = box->getText();
    }
}

//Updates filter parameters set by user 
void MainComponent::updateFilterSettings()
{
    //grab and store filter slider values
    auto cutoff = (float)cutoffSlider.getValue();
    auto resonance = (float)resonanceSlider.getValue();
    
    //handles band pass selection in combo box
    if (filterType == "Band Pass")
    {
        //set filter type to low pass and set cutoff and resonance parameters
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::bandPass;
        stateVariableFilter.state->setCutOffFrequency (globalSampleRate, cutoff, resonance);
    }
    
    //handles high pass selection in combo box
    else if (filterType == "High Pass")
    {
        //set filter type to low pass and set cutoff and resonance parameters
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::highPass;
        stateVariableFilter.state->setCutOffFrequency (globalSampleRate, cutoff, resonance);
    }
    //handles low pass selection in combo box
    else
    {
        //set filter type to low pass and set cutoff and resonance parameters
        stateVariableFilter.state->type = dsp::StateVariableFilter::Parameters<float>::Type::lowPass;
        stateVariableFilter.state->setCutOffFrequency (globalSampleRate, cutoff, resonance);
    }  
}

//Handles user changes in osc frequency from slider
void MainComponent::updateOscFrequency()
{
    //Determines even temperement tuning amount (one twelth movement based on octave below frequency) 
    auto fineTune = (((freqSlider.getValue() * oscMult) / 2) / 12) * fineTuneSlider.getValue();
    
    //Determine frequency addition/subtraction based on FM lfo phase and set depth value
    auto freqModAdd = lfoFreqTable[(int)lfoFreqPhase] * (lfoFreqDepthSlider.getValue()*100);
    
    //Determine next point in the osc wavetable for grabbing values
    //Multiply the current osc frequency (slider) by the wavetable size, then divide by the sample rate
    oscIncrement = ((freqSlider.getValue() * oscMult) + fineTune + freqModAdd) * oscTableSize / globalSampleRate;
    
    //"phase + increment" determines next part (phase) of osc table for grabbing values
    //"fmod" handles reaching past the osc table, and wrapping around to the appropriate phase from the beginning
    oscPhase = fmod((oscPhase + oscIncrement), oscTableSize);
}

//Handles user changes in lfo Amp frequency from slider
void MainComponent::updateLFOAmpFrequency()
{
    //Determine next point in the lfo Amp wavetable for grabbing values
    //Multiply the current lfo frequency (slider) by the wavetable size, then divide by the sample rate
    lfoIncrement = LfoAmp->getRateSliderValue() * lfoTableSize / globalSampleRate;
    
    //"phase + increment" determines next part (phase) of lfo Amp table for grabbing values
    //"fmod" handles reaching past the lfo table, and wrapping around to the appropriate phase from the beginning
    lfoPhase = fmod((lfoPhase + lfoIncrement), lfoTableSize);
}

//Handles user changes in lfo FM frequency from slider
void MainComponent::updateLFOFreqFrequency()
{
    //Determine next point in the lfo FM wavetable for grabbing values
    //Multiply the current lfo FM frequency (slider) by the wavetable size, then divide by the sample rate
    lfoFreqIncrement = (lfoFreqRateSlider.getValue()* 2) * lfoFreqTableSize / globalSampleRate;
    
    //"phase + increment" determines next part (phase) of lfo FM table for grabbing values
    //"fmod" handles reaching past the lfo FM table, and wrapping around to the appropriate phase from the beginning
    lfoFreqPhase = fmod((lfoFreqPhase + lfoFreqIncrement), lfoFreqTableSize);
}

//create wavetables for sine, sawtooth, square, and triangle
void MainComponent::createWavetables()
{
    //for loop handles calculations for inserting appropriate values into the table, sample to sample
    for (int i = 0; i < oscTableSize; i++)
    {
        //sine wave table for osc and amp lfo
        sineTable.insert(i , sin(2.0 * double_Pi * i / oscTableSize));   
        lfoAmpTable.insert(i , sin(2.0 * double_Pi * i / lfoTableSize));
        lfoFreqTable.insert(i , sin(2.0 * double_Pi * i / lfoFreqTableSize));   
        
        //saw wave table for osc (ramp up)
        sawTable.insert(i , ((i / oscTableSize) - 0.5) * 2);   
        
        //square wave table for osc
        if (i / oscTableSize < 0.5)     //first half of table (-1)
        {
            squareTable.insert(i, -1);
        }
        else                            //second half of table (1)
        {
            squareTable.insert(i, 1);
        }
        
        //triangle wave table for osc
        if (i / oscTableSize < 0.5)     //first half of table (ramp up)
        {
            triangleTable.insert(i , ((i / (oscTableSize/2)) - 0.5) * 2); 
        }
        else                            //second half ot table (ramp down)
        {
            triangleTable.insert(i, (0.5 - ((i - oscTableSize/2) / (oscTableSize/2))) * 2);
        }
    }
}

