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
    modules.add (new LfoModule (
        &lfoFreqRateSlider,
        &lfoFreqDepthSlider,
        &lfoFM
    ) );
    
    // OSCILLATORS
    modules.add (new OscillatorModule ( 
        &oscLevelSlider,
        &lengthBox,
        &fineTuneSlider,
        &freqSlider, 
        &oscBox
    ) );
    
    // OSCILLATORS -Two
    modules.add (new OscillatorModule ( 
        &oscLevelSliderTwo,
        &lengthBoxTwo,
        &fineTuneSliderTwo,
        &freqSliderTwo, 
        &oscBoxTwo
    ) );
    
    // LFO AMP
    modules.add (new LfoModule (
        &lfoAmpRateSlider,
        &lfoAmpDepthSlider,
        &lfoAmp
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
        &satTubeButton, // TAPE BUTTON
        &satTapeButton  // TUBE BUTTON
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
    oscBoxTwo.addListener(this);
    filterBox.addListener(this);
    lengthBox.addListener(this);
    lengthBoxTwo.addListener(this);
    satTubeButton.addListener(this);
    satTapeButton.addListener(this);
    
    //set window size
    setSize (1600, 800);
    
    //set audio channels to 0 Inputs and 2 Outputs(Stereo playback)
    setAudioChannels (0, 2);
    
    //set combo box selections ("8", sine, low pass)     
    lengthBox.setSelectedId(2);
    lengthBoxTwo.setSelectedId(2);
    oscBox.setSelectedId(1);
    oscBoxTwo.setSelectedId(1);    
    filterBox.setSelectedId(1);
    satType = 1;
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
    oscFrequencyTwo = freqSlider.getValue();
    lfoFrequency = lfoAmpRateSlider.getValue();
    lfoFreqFrequency = lfoFreqRateSlider.getValue();
        
    //set for starting at beginning of osc and lfo wavetables
    oscPhase = 0;
    oscPhaseTwo = 0;
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
    oscIncrementTwo = oscFrequencyTwo * oscTableSize / globalSampleRate;
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
 
    //initialize values for LinearSmoothedValue class
    smoothOscOneOutput.reset(sampleRate, 0.035);        //sample rate and ramp length
    smoothOscOneOutput.setValue(0.0);
    
    smoothOscTwoOutput.reset(sampleRate, 0.035);
    smoothOscTwoOutput.setValue(0.0);
    
    smoothLFOAmpDepth.reset(sampleRate, 0.035);
    smoothLFOAmpDepth.setValue(0.0);
    
    smoothDrive.reset(sampleRate, 0.035);
    smoothDrive.setValue(0.0);
    
    smoothOutput.reset(sampleRate, 0.035);
    smoothOutput.setValue(0.0);
}


//audio-processing - AudioSouceChannel -> where to get buffer and channel information
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) 
{
    //grab osc and lfo depth slider values
    auto oscLevel = (float) oscLevelSlider.getValue();
    auto oscLevelTwo = (float) oscLevelSliderTwo.getValue();
    auto lfoDepth = (float) lfoAmpDepthSlider.getValue();
    auto drive = (float) satDriveKnob.getValue();
    auto output = (float) outputLevelSlider.getValue();
    
    //set target smooth values
    smoothOscOneOutput.setValue(oscLevel);
    smoothOscTwoOutput.setValue(oscLevelTwo);
    smoothLFOAmpDepth.setValue(lfoDepth);
    smoothDrive.setValue(drive);
    smoothOutput.setValue(output);
    
    //create pointers to beginning of both channels' buffer (for writing)
    auto* channelOne = bufferToFill.buffer->getWritePointer (0, bufferToFill.startSample);
    auto* channelTwo = bufferToFill.buffer->getWritePointer( 1, bufferToFill.startSample);
    
    //loop with conditional statements handles osc selection (from wavetables) for writing to buffer
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        //grab the lfo (amp) phase position
        float lfoPhasePosition = lfoAmpTable[(int)lfoPhase];
       
        //Grab the samples from wavetables and add together (in accordance to current phase)
        //Multiply against the osc level slider to determine amplitude      
        if (smoothOscOneOutput.isSmoothing())
        {
            channelOne[sample] = (wavetableOne[(int)oscPhase] * smoothOscOneOutput.getNextValue()) + (wavetableTwo[(int)oscPhaseTwo] * oscLevelTwo);
            channelTwo[sample] = (wavetableOne[(int)oscPhase] * smoothOscOneOutput.getNextValue()) + (wavetableTwo[(int)oscPhaseTwo] * oscLevelTwo); 
        }
        else if (smoothOscTwoOutput.isSmoothing())
        {
            channelOne[sample] = (wavetableOne[(int)oscPhase] * oscLevel) + (wavetableTwo[(int)oscPhaseTwo] * smoothOscTwoOutput.getNextValue());
            channelTwo[sample] = (wavetableOne[(int)oscPhase] * oscLevel) + (wavetableTwo[(int)oscPhaseTwo] * smoothOscTwoOutput.getNextValue());             
        }
        else 
        {
            channelOne[sample] = (wavetableOne[(int)oscPhase] * oscLevel) + (wavetableTwo[(int)oscPhaseTwo] * oscLevelTwo);
            channelTwo[sample] = (wavetableOne[(int)oscPhase] * oscLevel) + (wavetableTwo[(int)oscPhaseTwo] * oscLevelTwo); 
        }
 
        //LFO Treatment - Wet to Dry Ratio
        if (smoothLFOAmpDepth.isSmoothing())
        {
            channelOne[sample] = ((channelOne[sample]) * (smoothLFOAmpDepth.getNextValue() * lfoPhasePosition)) + 
                                 ((channelOne[sample]) * (1.0 - smoothLFOAmpDepth.getNextValue()));
            channelTwo[sample] = ((channelTwo[sample]) * (smoothLFOAmpDepth.getNextValue() * lfoPhasePosition)) + 
                                 ((channelTwo[sample]) * (1.0 - smoothLFOAmpDepth.getNextValue()));
        }
        else
        {
            channelOne[sample] = ((channelOne[sample]) * (lfoDepth * lfoPhasePosition)) + 
                                 ((channelOne[sample]) * (1.0 - lfoDepth));
            channelTwo[sample] = ((channelTwo[sample]) * (lfoDepth * lfoPhasePosition)) + 
                                 ((channelTwo[sample]) * (1.0 - lfoDepth));  
        }
       
        //update osc and lfo frequencies/phases
        updateOscFrequency();
        updateOscFrequencyTwo();
        updateLFOAmpFrequency();
        updateLFOFreqFrequency();
    }
     
    //grab filled buffer and store in sample block (so we can use with the filter)
    dsp::AudioBlock<float> sampleBlock (*bufferToFill.buffer);
    
    //grab filter parameter settings
    updateFilterSettings();
    
    //process sample block (buffer) with the filter
    stateVariableFilter.process(dsp::ProcessContextReplacing<float> (sampleBlock));
    
    //Saturation Button One handling
    if (satType == 1)
    {
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            if (smoothDrive.isSmoothing())
            {
                channelOne[sample] = (channelOne[sample] * 0.9) + (smoothDrive.getNextValue() * channelOne[sample]);             
                channelTwo[sample] = (channelTwo[sample] * 0.9) + (smoothDrive.getNextValue() * channelTwo[sample]);
            }
            else
            {
                channelOne[sample] = (channelOne[sample] * 0.9) + (drive * channelOne[sample]);              
                channelTwo[sample] = (channelTwo[sample] * 0.9) + (drive * channelTwo[sample]);
            }
            
            if (channelOne[sample] > 1.0f) 
                {channelOne[sample] = 1.0f;}
                
            if (channelOne[sample] < -1.0f) 
                {channelOne[sample] = -1.0f;}
                
            if (channelTwo[sample] > 1.0f) 
                {channelTwo[sample] = 1.0f;}
                
            if (channelTwo[sample] < -1.0f) 
                {channelTwo[sample] = -1.0f;}
        }
    }
    
    //Saturation Button Two Handling
    if (satType == 2)
    {
        for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
        {
            if (smoothDrive.isSmoothing())
            {
                channelOne[sample] = (channelOne[sample] * 0.9) + (smoothDrive.getNextValue() * 3 * channelOne[sample]);             
                channelTwo[sample] = (channelTwo[sample] * 0.9) + (smoothDrive.getNextValue() * 3 * channelTwo[sample]);
            }
            else
            {
                channelOne[sample] = (channelOne[sample] * 0.9) + (drive * 3 * channelOne[sample]);              
                channelTwo[sample] = (channelTwo[sample] * 0.9) + (drive * 3 * channelTwo[sample]);
            }
            
            if (channelOne[sample] > 1.0f) 
                {channelOne[sample] = 1.0f;}
                
            if (channelOne[sample] < -1.0f) 
                {channelOne[sample] = -1.0f;}
                
            if (channelTwo[sample] > 1.0f) 
                {channelTwo[sample] = 1.0f;}
                
            if (channelTwo[sample] < -1.0f) 
                {channelTwo[sample] = -1.0f;}
        }
    }
     
    //output
    for (int sample = 0; sample < bufferToFill.numSamples; ++sample)
    {
        if(smoothOutput.isSmoothing())
        {
            channelOne[sample] = ((channelOne[sample]) * (smoothOutput.getNextValue() )); 
            channelTwo[sample] = ((channelTwo[sample]) * (smoothOutput.getNextValue() ));
        }
        else
        {
            channelOne[sample] = ((channelOne[sample]) * (output)); 
            channelTwo[sample] = ((channelTwo[sample]) * (output));
        }
    }
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
    Grid grid;
    
    using Track = Grid::TrackInfo;
        
    grid.templateRows    = {
        Track (1_fr),
        Track (1_fr)
    };
    
    grid.templateColumns = {
        Track (1_fr),
        Track (2_fr),
        Track (2_fr),
        Track (1_fr),
        Track (3_fr),
        Track (2_fr),
        Track (1_fr),
        Track (1_fr),
    };
    
    int numModules = modules.size();
    
    for (int i = 0; i < numModules; i++) {
        grid.items.add ( modules[i] );
    }

    grid.items.add ( scenes[0] );
        
    Rectangle<int> bounds = getLocalBounds();
    
    grid.performLayout ( bounds );
}

//Handles combo box changes - grab selection's text
void MainComponent::comboBoxChanged(ComboBox* box)
{
    //handles changes to filter type
    if (box == &filterBox)
    {
        filterType = box->getText();        
    }

    //handles changes to osc length type
    if (box  == &lengthBox || box == &lengthBoxTwo)
    {
        if (box == &lengthBox)
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
            
        if (box == &lengthBoxTwo)
        {
            //set osc length multiplier to appropriate value
            if (box->getText() == "4")
            {
                oscMultTwo = 0.5;   
            }
        
            else if (box->getText() == "8")
            {
                oscMultTwo = 1;   
            }
        
            else if (box->getText() == "16")
            {
                oscMultTwo = 2;   
            }
        }
    }
    
    //handles changes to osc type
    if (box == &oscBox || box == &oscBoxTwo)
    {
        if (box == &oscBox)
        {
            if (box->getText() == "Sine")
            {
                wavetableOne = sineTable;   
            }
            else if (box->getText() == "Saw")
            {
                wavetableOne = sawTable;   
            }
            else if (box->getText() == "Square")
            {
                wavetableOne = squareTable;   
            }
            else
            {
                wavetableOne = triangleTable;   
            }
        }
        
        if (box == &oscBoxTwo)
        {
            if (box->getText() == "Sine")
            {
                wavetableTwo = sineTable;   
            }
            else if (box->getText() == "Saw")
            {
                wavetableTwo = sawTable;   
            }
            else if (box->getText() == "Square")
            {
                wavetableTwo = squareTable;   
            }
            else
            {
                wavetableTwo = triangleTable;   
            }
        }
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

//Handles user changes in osc frequency from slider
void MainComponent::updateOscFrequencyTwo()
{
    auto fineTune = (((freqSliderTwo.getValue() * oscMultTwo) / 2) / 12) * fineTuneSliderTwo.getValue();
    
    auto freqModAdd = lfoFreqTable[(int)lfoFreqPhase] * (lfoFreqDepthSlider.getValue()*100);
    
    oscIncrementTwo = ((freqSliderTwo.getValue() * oscMultTwo) + fineTune + freqModAdd) * oscTableSize / globalSampleRate;
    
    oscPhaseTwo = fmod((oscPhaseTwo + oscIncrementTwo), oscTableSize);
}

//Handles user changes in lfo Amp frequency from slider
void MainComponent::updateLFOAmpFrequency()
{
    //Determine next point in the lfo Amp wavetable for grabbing values
    //Multiply the current lfo frequency (slider) by the wavetable size, then divide by the sample rate
    lfoIncrement = lfoAmpRateSlider.getValue() * lfoTableSize / globalSampleRate;
    
    //"phase + increment" determines next part (phase) of lfo Amp table for grabbing values
    //"fmod" handles reaching past the lfo table, and wrapping around to the appropriate phase from the beginning
    lfoPhase = fmod((lfoPhase + lfoIncrement), lfoTableSize);
}

//Handles user changes in lfo FM frequency from slider
void MainComponent::updateLFOFreqFrequency()
{
    lfoFreqIncrement = (lfoFreqRateSlider.getValue()* 2) * lfoFreqTableSize / globalSampleRate;
    
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

//Handle button click events - set appropriate saturation function
void MainComponent::buttonClicked(Button* button)
{
    if (button == &satTubeButton)
    {
        satType = 1;
    }
    
    else if(button == & satTapeButton)
    {
        satType = 2;
    }
    
}