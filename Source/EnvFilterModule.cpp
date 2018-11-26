/*
  ==============================================================================

    EnvFilterModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "EnvFilterModule.h"

EnvFilterModule::EnvFilterModule ( ) : Title ("FILTER ENVELOPE")
{
    //
    addAndMakeVisible ( AttackSlider );
    AttackSlider.setRange ( 0 , 100 );
    AttackSlider.setSliderStyle ( Slider::LinearVertical );
    AttackSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

    addAndMakeVisible ( DecaySlider );
    DecaySlider.setRange ( 0 , 100 );
    DecaySlider.setSliderStyle ( Slider::LinearVertical );
    DecaySlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

    addAndMakeVisible ( SustainSlider );
    SustainSlider.setRange ( 0 , 100 );
    SustainSlider.setSliderStyle ( Slider::LinearVertical );
    SustainSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

    addAndMakeVisible ( ReleaseSlider );
    ReleaseSlider.setRange ( 0 , 100 );
    ReleaseSlider.setSliderStyle ( Slider::LinearVertical );
    ReleaseSlider.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );

    addAndMakeVisible ( AttackSliderLabel );
    AttackSliderLabel.setText("A", dontSendNotification);
    AttackSliderLabel.setJustificationType( Justification::centred );

    addAndMakeVisible ( DecaySliderLabel );
    DecaySliderLabel.setText("D", dontSendNotification);
    DecaySliderLabel.setJustificationType( Justification::centred );

    addAndMakeVisible ( SustainSliderLabel );
    SustainSliderLabel.setText("S", dontSendNotification);
    SustainSliderLabel.setJustificationType( Justification::centred );
            
    addAndMakeVisible ( ReleaseSliderLabel );
    ReleaseSliderLabel.setText("R", dontSendNotification);
    ReleaseSliderLabel.setJustificationType( Justification::centred );
    
    LeftPanel = new LeftSide ( );
    addAndMakeVisible ( LeftPanel );
    
    // TITLE
    addAndMakeVisible( TitleLabel );
    TitleLabel.setText( Title, dontSendNotification );
    TitleLabel.setJustificationType( Justification::centred );
    
}

EnvFilterModule::~EnvFilterModule()
{
    delete LeftPanel;
}

void EnvFilterModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR); 
    buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );
}

void EnvFilterModule::resized ()
{
    //
    Grid grid;
    using Track = Grid::TrackInfo;

    grid.templateRows = { 
        Track (1_fr)
    };
    grid.templateColumns = { 
        Track (1_fr) 
    };
  
    grid.autoRows = Track (1_fr);
    grid.autoColumns = Track (1_fr);

    grid.items = {
        GridItem ( TitleLabel         ).withArea( 1, 1, 1, 7 ),
        
        GridItem ( LeftPanel          ).withArea( 2, 1, 10, 3 ),
        
        GridItem ( AttackSlider       ).withArea( 2, 3, 10, 4 ),
        GridItem ( DecaySlider        ).withArea( 2, 4, 10, 5 ),
        GridItem ( SustainSlider      ).withArea( 2, 5, 10, 6 ),
        GridItem ( ReleaseSlider      ).withArea( 2, 6, 10, 7 ),
	    
	    GridItem ( AttackSliderLabel  ).withArea( 10 , 3, 10, 4 ),
        GridItem ( DecaySliderLabel   ).withArea( 10 , 4, 10, 5 ),
        GridItem ( SustainSliderLabel ).withArea( 10 , 5, 10, 6 ),
        GridItem ( ReleaseSliderLabel ).withArea( 10 , 6, 10, 7 )
    };

    Rectangle <int> bounds = getLocalBounds();
    bounds = moduleInternalsBounds (bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS);

    grid.performLayout ( bounds );
}


void EnvFilterModule::comboBoxUpdate ( String text )
{
    LeftPanel->comboBoxUpdate( text );
}


String EnvFilterModule::getFilterType()
{
    return LeftPanel->getFilterType();
}


float EnvFilterModule::getCutoffKnobValue()
{
    return LeftPanel->getCutoffKnobValue();
}

void EnvFilterModule::setCutoffKnobValue( float v )
{
    LeftPanel->setCutoffKnobValue( v );
}


float EnvFilterModule::getResonanceKnobValue()
{
    return LeftPanel->getResonanceKnobValue();
}

void EnvFilterModule::setResonanceKnobValue( float v )
{
    LeftPanel->setResonanceKnobValue( v );
}

ComboBox& EnvFilterModule::getFilterBox()
{
    return LeftPanel->getFilterBox();
}


EnvFilterModule::LeftSide::LeftSide( )
{
    addAndMakeVisible ( CutoffKnob );
    CutoffKnob.setRange ( 20.0, 2000.0 );
    CutoffKnob.setSliderStyle ( Slider::RotaryVerticalDrag );
    CutoffKnob.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
    CutoffKnob.setValue(1000);
    
    addAndMakeVisible(CutoffLabel);
    CutoffLabel.setText("Cutoff", dontSendNotification);

    addAndMakeVisible ( ResonanceKnob );
    ResonanceKnob.setRange ( 1.0, 5.0 );
    ResonanceKnob.setSliderStyle ( Slider::RotaryVerticalDrag );
    ResonanceKnob.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
    ResonanceKnob.setValue(1);
    
    addAndMakeVisible(ResonanceLabel);
    ResonanceLabel.setText("Res", dontSendNotification);
    
    addAndMakeVisible(FilterBox);
    FilterBox.addItem("Low Pass", 1);
    FilterBox.addItem("Band Pass", 2);
    FilterBox.addItem("High Pass", 3);
    FilterBox.setSelectedId( 1 );
    
    addAndMakeVisible(FilterTypeLabel);
    FilterTypeLabel.setText("Filter Type", dontSendNotification);
}

EnvFilterModule::LeftSide::~LeftSide() {}

void EnvFilterModule::LeftSide::paint (Graphics& g)
{
}

void EnvFilterModule::LeftSide::resized ()
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


void EnvFilterModule::LeftSide::comboBoxUpdate ( String text )
{
    filterType = text;
    //printf("EnvFilter Combo Update\n");
}


String EnvFilterModule::LeftSide::getFilterType()
{
    return filterType; 
}


float EnvFilterModule::LeftSide::getCutoffKnobValue()
{
    return CutoffKnob.getValue();
}

void EnvFilterModule::LeftSide::setCutoffKnobValue( float v )
{
    CutoffKnob.setValue( v );
}


float EnvFilterModule::LeftSide::getResonanceKnobValue()
{
    return ResonanceKnob.getValue();
}

void EnvFilterModule::LeftSide::setResonanceKnobValue( float v )
{
    ResonanceKnob.setValue( v );
}


ComboBox& EnvFilterModule::LeftSide::getFilterBox()
{
    return FilterBox;
}









