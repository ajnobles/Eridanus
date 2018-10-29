/*
  ==============================================================================

    EnvFilterModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"


// ENV FILTER
class EnvFilterModule : public CustomComponent
{
public:
    EnvFilterModule ( Slider* as, Slider* ds, 
                      Slider* ss, Slider* rs,
                      Slider* ck, Slider* rk,
                      ComboBox *fB )                 
                    : AttackSlider (as), DecaySlider (ds), 
                      SustainSlider (ss), ReleaseSlider (rs)
                      
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
   
        addAndMakeVisible ( AttackSliderLabel );
        AttackSliderLabel.setText("A", dontSendNotification);

        addAndMakeVisible ( DecaySliderLabel );
        DecaySliderLabel.setText("D", dontSendNotification);

        addAndMakeVisible ( SustainSliderLabel );
        SustainSliderLabel.setText("S", dontSendNotification);
                
        addAndMakeVisible ( ReleaseSliderLabel );
        ReleaseSliderLabel.setText("R", dontSendNotification);
        
        LeftPanel = new LeftSide (ck, rk, fB);
        addAndMakeVisible ( LeftPanel );
        
    }
    
    void paint (Graphics& g) override
    {
        g.setColour (BORDER_COLOR); 
        buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

        // TEMP IDENTIFICATION TEXT
        g.drawText ("FILTER ENVELOPE", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

    }
    
    void resized () override
    {
        //
        Grid grid;
        using Track = Grid::TrackInfo;

        grid.templateRows = { 
            Track (1_fr) , 
            Track (10_fr) ,
            Track (1_fr)
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
            GridItem (ReleaseSlider),
            GridItem (nullptr),
            GridItem (AttackSliderLabel),
            GridItem (DecaySliderLabel),
            GridItem (SustainSliderLabel),
            GridItem (ReleaseSliderLabel)
        };

        Rectangle <int> bounds = getLocalBounds();
        bounds = moduleInternalsBounds (bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS);

        grid.performLayout ( bounds );
    }
    
    
    struct LeftSide : public CustomComponent
    {
        LeftSide( Slider* ck, Slider* rk, ComboBox *fB)
                : CutoffKnob (ck), ResonanceKnob (rk), 
                  FilterBox (fB)
        {
            addAndMakeVisible ( CutoffKnob );
            CutoffKnob->setRange ( 20.0, 2000.0 );
            CutoffKnob->setSliderStyle ( Slider::RotaryVerticalDrag );
            CutoffKnob->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );\
            CutoffKnob->setValue(1000);
            
            addAndMakeVisible(CutoffLabel);
            CutoffLabel.setText("Cutoff", dontSendNotification);

            addAndMakeVisible ( ResonanceKnob );
            ResonanceKnob->setRange ( 1.0, 5.0 );
            ResonanceKnob->setSliderStyle ( Slider::RotaryVerticalDrag );
            ResonanceKnob->setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
            ResonanceKnob->setValue(1);
            
            addAndMakeVisible(ResonanceLabel);
            ResonanceLabel.setText("Res", dontSendNotification);
            
            addAndMakeVisible(FilterBox);
            FilterBox->addItem("Low Pass", 1);
            FilterBox->addItem("Band Pass", 2);
            FilterBox->addItem("High Pass", 3);
            
            addAndMakeVisible(FilterTypeLabel);
            FilterTypeLabel.setText("Filter Type", dontSendNotification);
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
                Track (1_fr), 
                Track (1_fr), 
                Track (1_fr)
            };
            
            grid.templateColumns = { 
                Track (1_fr),
                Track (2_fr)
            };

            grid.items = {
                GridItem ( FilterTypeLabel ),
                GridItem ( FilterBox ),
                GridItem ( CutoffLabel ),
                GridItem ( CutoffKnob ),
                GridItem ( ResonanceLabel ),
                GridItem ( ResonanceKnob )
            };

            Rectangle <int> bounds = getLocalBounds();
            bounds = moduleInternalsBounds (bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS);

            grid.performLayout ( bounds );
        }

        Slider* CutoffKnob;
        Slider* ResonanceKnob;
        ComboBox *FilterBox;
        
        Label FilterTypeLabel;
        Label CutoffLabel;
        Label ResonanceLabel;
    };

private:            
    Slider* AttackSlider;
    Slider* DecaySlider;
    Slider* SustainSlider;
    Slider* ReleaseSlider;

    Label AttackSliderLabel;
    Label DecaySliderLabel;
    Label SustainSliderLabel;
    Label ReleaseSliderLabel;

    LeftSide* LeftPanel;
};

