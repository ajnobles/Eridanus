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

/*
void EnvFilterModule::comboBoxUpdate ( String text )
{
    LeftPanel->comboBoxUpdate( text );
}
*/

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

/*
ComboBox& EnvFilterModule::getFilterBox()
{
    return LeftPanel->getFilterBox();
}
*/

TextButton& EnvFilterModule::getFilterButton( FILTER type )
{
    switch (type) 
    {
        case LOWPASS:
            return LeftPanel->getLPButton();
            break;
        case HIGHPASS:
            return LeftPanel->getHPButton();
            break;
        case BANDPASS:
            return LeftPanel->getBPButton();
            break;
        default:
            cout << "getFilterButton ERROR" << endl;
    }
}
 
/*
void EnvFilterModule::filterButtonClicked( String text )
{

    cout << "filterButtonClicked  " << text << endl;
    if (text == "LP")
        LeftPanel->setFilterButton( LOWPASS );
    
    else if (text == "HP")
        LeftPanel->setFilterButton( HIGHPASS );
    
    else if (text == "BP")
        LeftPanel->setFilterButton( BANDPASS );
}
*/

void EnvFilterModule::setFilter( String text ) 
// void EnvFilterModule::setFilter( FILTER type ) 
{
    FILTER type = HIGHPASS;

    if (text == "LP") 
        type = LOWPASS;

    else if (text == "BP")
        type = BANDPASS;

    LeftPanel->setFilterButton( type );
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
    CutoffLabel.setJustificationType( Justification::centredBottom );

    addAndMakeVisible ( ResonanceKnob );
    ResonanceKnob.setRange ( 1.0, 5.0 );
    ResonanceKnob.setSliderStyle ( Slider::RotaryVerticalDrag );
    ResonanceKnob.setTextBoxStyle ( Slider::TextBoxBelow, true, 50, 20 );
    ResonanceKnob.setValue(1);
    
    addAndMakeVisible(ResonanceLabel);
    ResonanceLabel.setText("Res", dontSendNotification);
    ResonanceLabel.setJustificationType( Justification::centredBottom );
/*    
    addAndMakeVisible(FilterBox);
    FilterBox.addItem("Low Pass", 1);
    FilterBox.addItem("Band Pass", 2);
    FilterBox.addItem("High Pass", 3);
    FilterBox.setSelectedId( 1 );
    
    addAndMakeVisible(FilterTypeLabel);
    FilterTypeLabel.setText("Filter Type", dontSendNotification);
*/
    
    addAndMakeVisible( HP );
    HP.setButtonText( "HP" );

    addAndMakeVisible( LP );
    LP.setButtonText( "LP" );

    addAndMakeVisible( BP );
    BP.setButtonText( "BP" );

    setFilterButton( HIGHPASS );
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
    using Px    = Grid::Px;

    grid.templateRows = {  
        Track (1_fr)
    };
    
    grid.templateColumns = { 
        Track (2_fr)
    };

    grid.autoRows = Track (1_fr);
    grid.autoColumns = Track (1_fr);
    grid.setGap( Px (3_px) );

    grid.items = {
        GridItem ( HP             ).withArea( 1 , 1, 1 , 5 ),
        GridItem ( LP             ).withArea( 2 , 1, 2 , 5 ),
        GridItem ( BP             ).withArea( 3 , 1, 3 , 5 ),
        GridItem ( CutoffLabel    ).withArea( 4 , 1, 4 , 5 ),
        GridItem ( CutoffKnob     ).withArea( 5 , 1, 8 , 5 ),
        GridItem ( ResonanceLabel ).withArea( 8 , 1, 8 , 5 ),
        GridItem ( ResonanceKnob  ).withArea( 9 , 1, 12, 5 )
    };

    Rectangle <int> bounds = getLocalBounds();
    bounds = moduleInternalsBounds (bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS);

    grid.performLayout ( bounds );
}


void EnvFilterModule::LeftSide::comboBoxUpdate ( String text )
{
    filterType = text;
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

/*
ComboBox& EnvFilterModule::LeftSide::getFilterBox()
{
    return FilterBox;
}
*/

void EnvFilterModule::LeftSide::setFilterButton( FILTER type )
{
    switch ( type )
    {
        case HIGHPASS:
            HP.setEnabled( false );
            LP.setEnabled( true  );
            BP.setEnabled( true  );
            filterType = "High Pass";
            break;
        case LOWPASS:
            HP.setEnabled( true  );
            LP.setEnabled( false );
            BP.setEnabled( true  );
            filterType = "Low Pass";
            break;
        case BANDPASS:
            HP.setEnabled( true  );
            LP.setEnabled( true  );
            BP.setEnabled( false );
            filterType = "Band Pass";
            break;
        default:
            cout << "setFilterButton ERROR" << endl;
    }
}


TextButton& EnvFilterModule::LeftSide::getLPButton()
{
    return LP;
}


TextButton& EnvFilterModule::LeftSide::getHPButton()
{
    return HP;
}


TextButton& EnvFilterModule::LeftSide::getBPButton()
{
    return BP;
}







