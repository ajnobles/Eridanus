/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"

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

    
    // INPUT MODULE
    struct InputModule : public CustomComponent
    {
        InputModule (Slider* IS, Label* IL)
                    : InputSlider (IS), InputLabel (IL)
        {
            addAndMakeVisible ( InputSlider );  

            InputSlider->setRange ( 0, 100 );
            InputSlider->setSliderStyle ( Slider::LinearVertical );
            InputSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20);      
        }
        
        void paint (Graphics& g) override
        {
            g.setColour (BORDER_COLOR);

            buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );
            
            // TEMP IDENTIFICATION TEXT
            g.drawText ("INPUT", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

        }
        
        void resized () override
        {
            Grid grid;

            using Track = Grid::TrackInfo;

            grid.templateRows    = { Track (1_fr), Track (10_fr) };
            grid.templateColumns = { Track (1_fr) };

            grid.items = {
                GridItem ( nullptr ),
                GridItem ( InputSlider )
            };

            Rectangle <int> bounds = getLocalBounds();

            bounds = moduleInternalsBounds ( bounds,
                                             MODULE_INSIDE_OFFSET,
                                             OFFSET,
                                             THICKNESS);

            grid.performLayout ( bounds );

        }

        Slider* InputSlider;
        Label*  InputLabel;
    };

    // OscillatorModule
    struct OscillatorModule : public Component
    {
        OscillatorModule (Slider* ls, Label* ll, Slider* fs, Label* fl, ComboBox *oB) 
        : levelSlider (ls), levelLabel (ll), freqSlider (fs) , freqLabel (fl), oscBox (oB)
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
            // frequency slider, slider display attributes
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
            String text = "OscillatorModule ITEM";
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

    // AMP FILTER
    struct AmpFilterModule : public CustomComponent
    {
        AmpFilterModule ( Slider* as, Slider* ds, Slider* ss, Slider* rs,
                          Label*  al, Label*  dl, Label*  sl, Label*  rl)
                        : AttackSlider (as), DecaySlider (ds), 
                          SustainSlider (ss), ReleaseSlider (rs),
                          AttackSliderLabel (al), DecaySliderLabel (dl),
                          SustainSliderLabel (sl), ReleaseSliderLabel (rl)
        {
	    addAndMakeVisible ( AttackSlider );
	    AttackSlider->setRange ( 0, 100 );
	    AttackSlider->setSliderStyle ( Slider::LinearVertical );
	    AttackSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

	    addAndMakeVisible ( DecaySlider );
	    DecaySlider->setRange ( 0, 100 );
	    DecaySlider->setSliderStyle ( Slider::LinearVertical );
	    DecaySlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

	    addAndMakeVisible ( SustainSlider );
	    SustainSlider->setRange ( 0, 100 );
	    SustainSlider->setSliderStyle ( Slider::LinearVertical );
	    SustainSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

	    addAndMakeVisible ( ReleaseSlider );
	    ReleaseSlider->setRange ( 0, 100 );
	    ReleaseSlider->setSliderStyle ( Slider::LinearVertical );
	    ReleaseSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
        }

        void paint (Graphics& g) override
        {
            g.setColour (BORDER_COLOR);
            buildModuleBorder (g, CORNERSIZE, THICKNESS, OFFSET);

            // TEMP IDENTIFICATION TEXT
            g.drawText ("AmpFILTER", 0, 25, getWidth(), getHeight(), Justification::centredTop); 
        }

        void resized () override
        {
            // 
            Grid grid;

            using Track = Grid::TrackInfo;

            grid.templateRows = { Track (1_fr), Track (10_fr) };
            grid.templateColumns = { Track (1_fr), Track (1_fr), Track (1_fr), Track (1_fr) };

            grid.items = {
                GridItem ( nullptr ),
                GridItem ( nullptr ),
                GridItem ( nullptr ),
                GridItem ( nullptr ),
                GridItem ( AttackSlider  ),
                GridItem ( DecaySlider   ),
                GridItem ( SustainSlider ),
                GridItem ( ReleaseSlider )
            };

            Rectangle <int> bounds = getLocalBounds();
            bounds = moduleInternalsBounds ( bounds,
                                             MODULE_INSIDE_OFFSET,
                                             OFFSET,
                                             THICKNESS);

            grid.performLayout ( bounds );
        }

        Slider* AttackSlider;
        Slider* DecaySlider;
        Slider* SustainSlider;
        Slider* ReleaseSlider;
 
        Label* AttackSliderLabel;
        Label* DecaySliderLabel;
        Label* SustainSliderLabel;
        Label* ReleaseSliderLabel;
    };

  
    // ENV FILTER
    struct EnvFilterModule : public CustomComponent
    {
        EnvFilterModule ( Slider* as, Slider* ds, 
                          Slider* ss, Slider* rs,
                          Slider* ck, Slider* rk,
                          TextButton* hpb,
                          TextButton* lpb,
                          TextButton* bpb,
                          Label*  al, Label*  dl, 
                          Label*  sl, Label*  rl )                 
                        : AttackSlider (as), DecaySlider (ds), 
                          SustainSlider (ss), ReleaseSlider (rs),
                          AttackSliderLabel (al), DecaySliderLabel (dl),
                          SustainSliderLabel (sl), ReleaseSliderLabel (rl)
                          
        {
            //
            addAndMakeVisible ( AttackSlider );
            AttackSlider->setRange ( 0 , 100 );
            AttackSlider->setSliderStyle ( Slider::LinearVertical );
            AttackSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

            addAndMakeVisible ( DecaySlider );
            DecaySlider->setRange ( 0 , 100 );
            DecaySlider->setSliderStyle ( Slider::LinearVertical );
            DecaySlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

            addAndMakeVisible ( SustainSlider );
            SustainSlider->setRange ( 0 , 100 );
            SustainSlider->setSliderStyle ( Slider::LinearVertical );
            SustainSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

            addAndMakeVisible ( ReleaseSlider );
            ReleaseSlider->setRange ( 0 , 100 );
            ReleaseSlider->setSliderStyle ( Slider::LinearVertical );
            ReleaseSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

            LeftPanel = new LeftSide (ck, rk, hpb, lpb, bpb);
            addAndMakeVisible ( LeftPanel );
            
        }
        
        void paint (Graphics& g) override
        {
            g.setColour (BORDER_COLOR); 
            buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

            // TEMP IDENTIFICATION TEXT
            g.drawText ("EnvFILTER", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

        }
        
        void resized () override
        {
            //
            Grid grid;
            using Track = Grid::TrackInfo;

            grid.templateRows = { 
                Track (1_fr) , 
                Track (10_fr) 
            };
            
            grid.templateColumns = { 
                Track (3_fr), 
                Track (1_fr), 
                Track (1_fr), 
                Track (1_fr), 
                Track (1_fr)
            };

            grid.items = {
                GridItem (nullptr),
                GridItem (nullptr),
                GridItem (nullptr),
                GridItem (nullptr),
                GridItem (nullptr),
                GridItem ( LeftPanel ),
                GridItem (AttackSlider),
                GridItem (DecaySlider),
                GridItem (SustainSlider),
                GridItem (ReleaseSlider)
            };

            Rectangle <int> bounds = getLocalBounds();
            bounds = moduleInternalsBounds (bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS);

            grid.performLayout ( bounds );
        }
        
        
        struct LeftSide : public CustomComponent
        {
            LeftSide( Slider* ck, Slider* rk, TextButton* hpb, TextButton* lpb, TextButton* bpb)
                    : CutoffKnob (ck), ResonanceKnob (rk), 
                      HighPassButton (hpb), LowPassButton (lpb), BandPassButton (bpb)
            {
                //
                addAndMakeVisible ( CutoffKnob );
                CutoffKnob->setRange ( 0, 100 );
                CutoffKnob->setSliderStyle ( Slider::Rotary );
                CutoffKnob->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

                addAndMakeVisible ( ResonanceKnob );
                ResonanceKnob->setRange ( 0, 100 );
                ResonanceKnob->setSliderStyle ( Slider::Rotary );
                ResonanceKnob->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );            
            }

            void paint (Graphics& g) override
            {
            }
            
            void resized () override
            {
                //
                Grid grid;

                using Track = Grid::TrackInfo;

                grid.templateRows = { 
                    Track (1_fr) ,
                    Track (1_fr) , 
                    Track (1_fr), 
                    Track (1_fr) , 
                    Track (1_fr)
                };
                
                grid.templateColumns = { 
                    Track (1_fr) 
                };

                grid.items = {
                    GridItem ( nullptr ),
                    GridItem ( nullptr ),
                    GridItem ( nullptr ),
                    GridItem ( CutoffKnob ),
                    GridItem ( ResonanceKnob )
                };

                Rectangle <int> bounds = getLocalBounds();
                bounds = moduleInternalsBounds (bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS);

                grid.performLayout ( bounds );
            }

            Slider* CutoffKnob;
            Slider* ResonanceKnob;

            TextButton* HighPassButton;
            TextButton* LowPassButton;
            TextButton* BandPassButton;
        };
                
        Slider* AttackSlider;
        Slider* DecaySlider;
        Slider* SustainSlider;
        Slider* ReleaseSlider;
 
        Label* AttackSliderLabel;
        Label* DecaySliderLabel;
        Label* SustainSliderLabel;
        Label* ReleaseSliderLabel;

        LeftSide* LeftPanel;
    };
   
    // LFO
    struct LfoModule : public CustomComponent
    {
        LfoModule (Slider* rs, Slider* ds, Label* rl, Label* dl)
            : RateSlider (rs), DepthSlider (ds), RateLabel (rl), DepthLabel (dl)
        {
            
            addAndMakeVisible ( RateSlider );
            RateSlider->setRange ( 0, 100 );
            RateSlider->setSliderStyle ( Slider::LinearVertical );
            RateSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
           

            addAndMakeVisible ( DepthSlider );
            DepthSlider->setRange ( 0, 100 );
            DepthSlider->setSliderStyle ( Slider::LinearVertical );
            DepthSlider->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );        
        
        }    
            
        void paint (Graphics& g) override
        {
            g.setColour (BORDER_COLOR);

            CustomComponent::buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

            // TEMP IDENTIFICATION TEXT
            g.drawText ("LFO", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

        }
        
        void resized () override
        {
            // 
            Grid grid;

            using Track = Grid::TrackInfo;

            grid.templateRows    = { Track (1_fr), Track (10_fr) };
            grid.templateColumns = { Track (1_fr), Track (1_fr) };

            grid.items = {
                GridItem ( nullptr ), 
                GridItem ( nullptr ), 
                GridItem ( RateSlider ),
                GridItem ( DepthSlider )
            };

            Rectangle <int> bounds = getLocalBounds();
            bounds = moduleInternalsBounds ( bounds, 
                                             MODULE_INSIDE_OFFSET, 
                                             OFFSET, 
                                             THICKNESS);

            grid.performLayout ( bounds );
        }

        Slider* RateSlider;
        Slider* DepthSlider;
        
        Label*  RateLabel;
        Label*  DepthLabel;
    };
    
    // SATURATION
    struct SaturationModule : public CustomComponent
    {
        SaturationModule ( Slider* dk,
                           TextButton* tapeB,
                           TextButton* tubeB )
                         : DriveKnob (dk), TapeButton (tapeB), TubeButton (tubeB)
        {
            //
            addAndMakeVisible ( DriveKnob );
            DriveKnob->setRange ( 0, 100 );
            DriveKnob->setSliderStyle ( Slider::Rotary );
            DriveKnob->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

            addAndMakeVisible ( TapeButton );
            TapeButton->setButtonText ( "TB" );

            addAndMakeVisible ( TubeButton );
            TubeButton->setButtonText ( "TB" );
        }

                      
        void paint (Graphics& g) override 
        {
            g.setColour (BORDER_COLOR);

            buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );
            // TEMP IDENTIFICATION TEXT
            g.drawText ("SATURATION", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

        }

        void resized () override
        {
            // 
            Grid grid;

            using Track = Grid::TrackInfo;

            grid.templateRows = {
                Track (1_fr),
                Track (1_fr),
                Track (1_fr),
                Track (2_fr),
            };
            
            grid.templateColumns = { Track (1_fr) };

            grid.items = {
                GridItem (nullptr),
                GridItem ( TapeButton ),
                GridItem ( TubeButton ),
                GridItem ( DriveKnob )
            };

            Rectangle <int> bounds = getLocalBounds();

            bounds = moduleInternalsBounds ( bounds,
                                             MODULE_INSIDE_OFFSET,
                                             OFFSET,
                                             THICKNESS);


            grid.performLayout ( bounds );
        }
        
        Slider* DriveKnob;
        
        TextButton* TapeButton;
        TextButton* TubeButton;
    };
   
    // OUTPUT
    struct OutputModule : public CustomComponent
    {
        OutputModule (Slider* os, Slider* ofs,
                      Label* ol,  Label* ofl)
                    : OutputSlider ( os ),
                      OutputFeedbackSlider ( ofs ),
                      OutputSliderLabel (ol),
                      OutputFeedbackLabel (ofl)
        {
            //
            addAndMakeVisible ( OutputSlider );
            OutputSlider->setRange ( 0, 100, 0 );
            OutputSlider->setSliderStyle (Slider::LinearVertical);
            OutputSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 50, 20);

            addAndMakeVisible ( OutputFeedbackSlider );
            OutputFeedbackSlider->setRange ( 0.0, 100.0, 1.0 );
            OutputFeedbackSlider->setSliderStyle ( Slider::LinearBarVertical );
            OutputFeedbackSlider->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
            OutputFeedbackSlider->setValue (50.0f);


        }
        
        void paint (Graphics& g) override
        {
            g.setColour (BORDER_COLOR);

            CustomComponent::buildModuleBorder( g, CORNERSIZE, THICKNESS, OFFSET );
            // TEMP IDENTIFICATION TEXT
            g.drawText ("OUTPUT", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

        }
        
        void resized () override
        {

            Grid grid;

            using Track = Grid::TrackInfo;

            grid.templateRows = { Track (1_fr), Track (10_fr) };
            grid.templateColumns = { Track (1_fr) , Track (1_fr) };

            grid.items = {
                GridItem ( nullptr ),
                GridItem ( nullptr ),
                GridItem ( OutputSlider ),
                GridItem ( OutputFeedbackSlider )
            };

            Rectangle<int> bounds = getLocalBounds();

            bounds = moduleInternalsBounds ( bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS );

            grid.performLayout ( bounds );
        }

        Slider* OutputSlider;
        Label* OutputSliderLabel;

        Slider* OutputFeedbackSlider;
        Label* OutputFeedbackLabel;

    };
 
    

        
private:
    //==============================================================================
    // Your private member variables go here...
    Random random;      //for random float number (0 - 1) generation for noise generator


    OwnedArray<Component> modules;
    
    // INPUT MODULE
    Slider InputLevelSlider;
    Label  InputLevelSliderLabel;
    
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
