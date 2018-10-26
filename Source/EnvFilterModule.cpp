/*
  ==============================================================================

    EnvFilterModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "EnvFilterModule.h"


EnvFilterModule::EnvFilterModule ( Slider* as, Slider* ds, 
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

EnvFilterModule::~EnvFilterModule ()
{
    delete LeftPanel;
}

void EnvFilterModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR); 
    buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

    // TEMP IDENTIFICATION TEXT
    g.drawText ("EnvFILTER", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

}

void EnvFilterModule::resized ()
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


// LEFT SIDE PANEL
EnvFilterModule::LeftSide::LeftSide ( Slider* ck, Slider* rk, TextButton* hpb, TextButton* lpb, TextButton* bpb)
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

void EnvFilterModule::LeftSide::paint (Graphics& g)
{
}

void EnvFilterModule::LeftSide::resized ()
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




