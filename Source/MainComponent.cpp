/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent()
{
    // INPUT
    Input = new InputModule();
    modules.add ( Input );
    
    // LFO FREQ
    modules.add (new LfoModule (
        &lfoFreqRateSlider,
        &lfoFreqDepthSlider// ,
        // &lfoFreqRateLabel,
        // &lfoFreqRateLabel
    ) );
    
    // OSCILLATORS
    modules.add (new OscillatorModule ( 
        &oscLevelSlider, 
        &oscLevelLabel, 
        &freqSlider, 
        &freqLabel,
        &oscBox
    )
    );
    
    // LFO AMP
    LfoAmp = new LfoModule(
    // modules.add (new LfoModule (
        &lfoAmpRateSlider,
        &lfoAmpDepthSlider// ,
        // &lfoAmpRateLabel,
        // &lfoAmpRateLabel
    ); 
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
        &ampCutoffKnob,
        &ampResonanceKnob,
        &ampHighPassButton,
        &ampLowPassButton,        
        &ampBandPassButton,
        &ampAttackLabel,
        &ampDecayLabel,
        &ampSustainLabel,
        &ampReleaseLabel
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
    freqSlider.addListener(this);
    oscLevelSlider.addListener(this);
    oscBox.addListener(this);

    //add filter combo box, set selections w/ text, and listener
//    addAndMakeVisible(filterBox);
    filterBox.addItem("Low Pass", 1);
    filterBox.addItem("Band Pass", 2);
    filterBox.addItem("High Pass", 3);
    filterBox.addListener(this);
    
    //add filter cutoff slider, slider display attributes, and listener 
//    addAndMakeVisible(cutoffSlider);
    cutoffSlider.setRange(20, 2000);
    cutoffSlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
    cutoffSlider.addListener(this);
    
    //add cutoff slider label and set text
//    addAndMakeVisible(cutoffLabel);
    cutoffLabel.setText("Cutoff", dontSendNotification);

    //add resonance slider, slider display attributes, and listener 
//    addAndMakeVisible(resonanceSlider);
    resonanceSlider.setRange(1, 5);
    resonanceSlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
    resonanceSlider.addListener(this);
    
    //add resonance slider label and set text
//    addAndMakeVisible(resonanceLabel);
    resonanceLabel.setText("Resonance", dontSendNotification);

    //add noise level slider, slider display attributes, and listener 
//    addAndMakeVisible(lfoAmpRateSlider);
//    lfoAmpRateSlider.setRange(0.0, 5.0);
//    lfoAmpRateSlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
//    lfoAmpRateSlider.addListener(this);
    
    //add noise level slider label and set text
//    addAndMakeVisible(lfoAmpRateLabel);
//    lfoAmpRateLabel.setText("LFO Amp Rate", dontSendNotification); 
    
    //add noise level slider, slider display attributes, and listener 
//    addAndMakeVisible(lfoAmpDepthSlider);
//    lfoAmpDepthSlider.setRange(0.0, 1.0);
//    lfoAmpDepthSlider.setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
//    lfoAmpDepthSlider.addListener(this);
    
    //add noise level slider label and set text
//    addAndMakeVisible(lfoAmpDepthLabel);
//    lfoAmpDepthLabel.setText("LFO Amp Depth", dontSendNotification);
    
    //set window size
    setSize (1600, 800);
    
    //set audio channels to 0 Inputs and 2 Outputs(Stereo playback)
    setAudioChannels (0, 2);
    
    //set filter combo box to low pass filter
    filterBox.setSelectedId(1);
    
    //set osc combo box to sine
    oscBox.setSelectedId(1);
    
    //set sliders for osc and filter controls
    cutoffSlider.setValue(1000);
    lfoAmpRateSlider.setValue(1.0);
    lfoAmpDepthSlider.setValue(0.0);

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
    //output audio device's information to console
    String messageToConsole;
    messageToConsole << "Samples per Block: " << samplesPerBlockExpected << newLine;
    messageToConsole << "Sample Rate: " << sampleRate;
    Logger::getCurrentLogger()->writeToLog (messageToConsole);
    
    //grab sampleRate for filter settings
    globalSampleRate = sampleRate;   
    
    //grab osc and lfo slider frequency values 
    oscFrequency = freqSlider.getValue();
    lfoFrequency = lfoAmpRateSlider.getValue();
    
    //set for starting at beginning of osc and lfo wavetables
    oscPhase = 0;
    lfoPhase = 0;
    
    //set wavetable size
    oscTableSize = 1024;
    lfoTableSize = 1024;

    //Determine increment size to find the next point in the osc wavetable for grabbing values 
    //Multiply the current osc frequency by the wavetable size, then divide by the sample rate
    //Note: initialized here, but modifiable via functions 
    oscIncrement = oscFrequency * oscTableSize / globalSampleRate;
    lfoIncrement = lfoFrequency * lfoTableSize / globalSampleRate;
    
    //create wavetables for sine, sawtooth, square, and triangle
    //for loop handles calculations for inserting appropriate values into the table, sample to sample
    for (int i = 0; i < oscTableSize; i++)
    {
        //sine wave table for osc and amp lfo
        sineTable.insert(i , sin(2.0 * double_Pi * i / oscTableSize));   
        lfoAmpTable.insert(i , sin(2.0 * double_Pi * i / lfoTableSize));   
        
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
    auto lfoDepth = (float) lfoAmpDepthSlider.getValue();
        
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
       
       //update osc and lfo frequencies
       updateOscFrequency();
       updateLFOAmpFrequency();
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
/*
    g.setFont (Font (16.0f));
    g.setColour (Colours::white);
    g.drawText ("Hello World!", getLocalBounds(), Justification::centred, true);
*/
}

void MainComponent::resized()
{
    // This is called when the MainComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.

    // SynthScene.setBounds (0, 0, getWidth(), getHeight() / 2.0f);
    // KeyboardScene.setBounds (0, getHeight() / 2.0f, getWidth(), getHeight() / 2.0f);


    Grid grid;
    
    using Track = Grid::TrackInfo;
        
    grid.templateRows    = {
        Track (1_fr),
        Track (1_fr),
        Track (2_fr)
    };
    
    grid.templateColumns = {
        Track (1_fr),
        Track (1_fr),
        Track (2_fr),
        Track (1_fr),
        Track (2_fr),
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

/*
    //Set size and location of filter combo box 
    oscBox.setBounds((getWidth()/2)-50, 10, 100, 20);
    
    //Set size and location of level slider and label 
    oscLevelSlider.setBounds (100, 40, getWidth() - 110, 20);
    oscLevelLabel.setBounds (10, 40, 90, 20);

    //Set size and location of level slider and label 
    freqSlider.setBounds (100, 70, getWidth() - 110, 20);
    freqLabel.setBounds (10, 70, 90, 20);

    //Set size and location of cutoff slider and label 
    lfoAmpRateSlider.setBounds (100, 100, getWidth() - 110, 20);
    lfoAmpRateLabel.setBounds (10, 100, 90, 20);
    
    //Set size and location of cutoff slider and label 
    lfoAmpDepthSlider.setBounds (100, 130, getWidth() - 110, 20);
    lfoAmpDepthLabel.setBounds (10, 130, 90, 20);
    
    //Set size and location of filter combo box 
    filterBox.setBounds((getWidth()/2)-50, 160, 100, 20);
    
    //Set size and location of cutoff slider and label 
    cutoffSlider.setBounds (100, 190, getWidth() - 110, 20);
    cutoffLabel.setBounds (10, 190, 90, 20);
    
    //Set size and location of cutoff slider and label 
    resonanceSlider.setBounds (100, 220, getWidth() - 110, 20);
    resonanceLabel.setBounds (10, 220, 90, 20);
*/
}

//Handles combo box changes - grab selection's text
void MainComponent::comboBoxChanged(ComboBox* box)
{
    //handles changes to filter type
    if (box->getText() == "Low Pass" || box->getText() == "Band Pass" || box->getText() == "High Pass")
    {
        filterType = box->getText();
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
    //Determine next point in the osc wavetable for grabbing values
    //Multiply the current osc frequency (slider) by the wavetable size, then divide by the sample rate
    oscIncrement = freqSlider.getValue() * oscTableSize / globalSampleRate;
    
    //"phase + increment" determines next part (phase) of osc table for grabbing values
    //"fmod" handles reaching past the osc table, and wrapping around to the appropriate phase from the beginning
    oscPhase = fmod((oscPhase + oscIncrement), oscTableSize);
}

//Handles user changes in lfo frequency from slider
void MainComponent::updateLFOAmpFrequency()
{
    //Determine next point in the lfo wavetable for grabbing values
    //Multiply the current lfo frequency (slider) by the wavetable size, then divide by the sample rate
    lfoIncrement = lfoAmpRateSlider.getValue() * lfoTableSize / globalSampleRate;
    
    //"phase + increment" determines next part (phase) of lfo table for grabbing values
    //"fmod" handles reaching past the lfo table, and wrapping around to the appropriate phase from the beginning
    lfoPhase = fmod((lfoPhase + lfoIncrement), lfoTableSize);
}
