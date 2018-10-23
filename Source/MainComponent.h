/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


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

    void OSC_Test () 
    {
        //
    }

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
        else if (slider == &lfoAmpRateSlider)
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


    // OSC
    struct OSC : public Component
    {
        OSC (Slider* ls, Label* ll, Slider* fs, Label* fl, ComboBox *oB) 
            : levelSlider (ls), levelLabel (ll),
              freqSlider (fs) , freqLabel (fl),
              oscBox (oB)
        {

            // LEVEL
            addAndMakeVisible ( levelSlider );
            levelSlider->setRange ( 0.0f, 0.5f );
            levelSlider->setTextBoxStyle ( Slider::TextBoxBelow, false, 100, 20 );
            levelSlider->setValue(0.240);
            // levelSlider->setSliderStyle ( Slider::LinearVertical );
            
            addAndMakeVisible(levelLabel);
            levelLabel->setText("Osc Level", dontSendNotification);   
            
            // FREQ
			//add frequency slider, slider display attributes
			addAndMakeVisible(freqSlider);
			freqSlider->setRange(200.0, 1000.0);
			freqSlider->setTextBoxStyle(Slider::TextBoxRight, false, 100, 20);
            freqSlider->setValue(400);

			//add frequency slider label and set text
			addAndMakeVisible(freqLabel);
			freqLabel->setText("Frequency", dontSendNotification);
			
            // COMBO BOX
			addAndMakeVisible(oscBox);
			oscBox->addItem("Sine", 1);
			oscBox->addItem("Saw", 2);
			oscBox->addItem("Square", 3);
			oscBox->addItem("Triangle", 4);        
        }

        void paint (Graphics& g) override
        {
            Colour colour = Colours::lightblue;
            String text = "OSC ITEM";
            g.fillAll (colour.withAlpha (0.5f));

            g.setColour (Colours::black);
            g.drawText (text, getLocalBounds().withSizeKeepingCentre (100, 100),
                    Justification::centred, false);
        }

        void resized () override
        {
            Grid grid;
            using Track = Grid::TrackInfo;

            grid.templateRows = { Track (1_fr) };
            grid.templateColumns = { Track (1_fr) };
          
            grid.autoRows = Track (1_fr);
            grid.autoColumns = Track (1_fr);

            grid.items = {
                GridItem ( oscBox      ),
                GridItem ( levelSlider ),
                GridItem ( freqSlider  )
            };

            grid.performLayout ( getLocalBounds() );
        }

        Slider* levelSlider;
        Slider* freqSlider;
        Label*  levelLabel;
        Label*  freqLabel;
        ComboBox* oscBox;
    };
        
private:
    //==============================================================================
    // Your private member variables go here...
    Random random;      //for random float number (0 - 1) generation for noise generator


    OwnedArray<Component> modules;
    
    
    //sliders for osc and filter controls
    Slider oscLevelSlider;

    Slider freqSlider;
    Slider cutoffSlider;
    Slider resonanceSlider;
    Slider lfoAmpRateSlider;
    Slider lfoAmpDepthSlider;
    
    //labels for osc and filter
    Label oscLevelLabel;

    Label freqLabel;
    Label cutoffLabel;
    Label resonanceLabel;
    Label lfoAmpRateLabel;
    Label lfoAmpDepthLabel;

    //combo boxes osc and filter types
    ComboBox filterBox;     
    ComboBox oscBox;     

    //strings hold osc and filter selections
    String filterType;      
    String oscType;
    
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
