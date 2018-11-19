/*
  ==============================================================================

    OscillatorModule.cpp
    Created: 25 Oct 2018 7:09:22am
    Author:  allen

  ==============================================================================
*/

#include "OscillatorModule.h"

OscillatorModule::OscillatorModule ( ) 
{
    // LEVEL
    addAndMakeVisible ( levelSlider );
    levelSlider.setRange ( 0.0f, 0.3f );
    levelSlider.setTextBoxStyle ( Slider::TextBoxRight, false, 50, 20 );
    levelSlider.setValue(0.0);
    levelSlider.setSliderStyle ( Slider::LinearHorizontal );
            
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Osc Output", dontSendNotification);   
    
    // FREQ
    // frequency slider, slider display attributes
    //addAndMakeVisible(freqSlider);
    freqSlider.setRange(200.0, 1000.0);
    freqSlider.setTextBoxStyle(Slider::TextBoxRight, false, 50, 20);
    freqSlider.setValue(400);
    
    //addAndMakeVisible(freqLabel);
    //freqLabel.setText("Osc Freq", dontSendNotification);
    
    // FINE TUNE
    addAndMakeVisible(fineTuneSlider);
    fineTuneSlider.setRange(-1.0, 1.0);
    fineTuneSlider.setTextBoxStyle(Slider::TextBoxRight, false, 50, 20);
    fineTuneSlider.setValue(0.0);
    
    addAndMakeVisible(fineTune);
    fineTune.setText("Fine Tune", dontSendNotification);
    
    freqSlider.setSliderStyle ( Slider::LinearHorizontal );
    
    //add frequency slider label and set text
    //addAndMakeVisible(freqLabel);
    //freqLabel.setText("Freq", dontSendNotification);
	        
    // COMBO BOX
    addAndMakeVisible(oscBox);
    oscBox.addItem("Sine", 1);
    oscBox.addItem("Saw", 2);
    oscBox.addItem("Square", 3);
    oscBox.addItem("Triangle", 4);
    
    addAndMakeVisible(oscTypeLabel);
    oscTypeLabel.setText("Osc Type", dontSendNotification);
    
    // LENGTH COMBO BOX
    addAndMakeVisible(lengthBox);
    lengthBox.addItem("4", 1);
    lengthBox.addItem("8", 2);
    lengthBox.addItem("16", 3);
        
    addAndMakeVisible(oscLength);
    oscLength.setText("Osc Length", dontSendNotification);
    oscBox.setSelectedId( 1 );    
    lengthBox.setSelectedId( 2 );
}


OscillatorModule::~OscillatorModule() {}


void OscillatorModule::paint (Graphics& g)
{

    g.setColour ( BORDER_COLOR );
    buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );

}


void OscillatorModule::resized ()
{

    Grid grid;
    using Track = Grid::TrackInfo;

    grid.templateRows = { Track (1_fr) };
    grid.templateColumns = { Track (1_fr), Track (3_fr) };
  
    grid.autoRows = Track (1_fr);
    grid.autoColumns = Track (1_fr);

    grid.items = {
        GridItem ( oscTypeLabel ),
        GridItem ( oscBox       ),
        GridItem ( oscLength    ),
        GridItem ( lengthBox    ),
        GridItem ( fineTune     ),
        GridItem ( fineTuneSlider),
        GridItem ( levelLabel   ),
        GridItem ( levelSlider  )
        //GridItem ( freqLabel    )
        //GridItem ( freqSlider   )
    };

    grid.performLayout ( getLocalBounds() );

}



void OscillatorModule::comboBoxUpdate( String text )
// void OscillatorModule::comboBoxChanged ( ComboBox* box )
{
    // String text = box->getText();
    
    if (text == "4")
        oscMult = 0.5;

    else if (text  == "8")
        oscMult = 1.0;

    else if (text == "16")
        oscMult = 2;

    else if (text == "Sine" || text == "Saw"|| text == "Square"|| text == "Triangle")
        oscType = text;

}

bool OscillatorModule::isLevelSlider( Slider* slider )
{
    return slider == &levelSlider;
}


bool OscillatorModule::isFreqSlider( Slider* slider )
{
    return slider == &freqSlider;
}


bool OscillatorModule::isFineTuneSlider( Slider* slider )
{
    return slider == &fineTuneSlider;
}


float OscillatorModule::getLevelSliderValue()
{
    return levelSlider.getValue();
}


void OscillatorModule::setLevelSliderValue( float v )
{
    levelSlider.setValue( v );
}



float OscillatorModule::getFreqSliderValue()
{
    return freqSlider.getValue();
}


void OscillatorModule::setFreqSliderValue( float v )
{
    freqSlider.setValue( v );
}


float OscillatorModule::getFineTuneSliderValue()
{
    return fineTuneSlider.getValue();
}


void OscillatorModule::setFineTuneSliderValue( float v )
{
    fineTuneSlider.setValue( v );
}


ComboBox& OscillatorModule::getOscBox()
{
    return oscBox;
}

ComboBox& OscillatorModule::getLengthBox()
{
    return lengthBox;
}

void OscillatorModule::setOscMult( float v )
{
    oscMult = v;
}


float OscillatorModule::getOscMult( )
{
    return oscMult;
}


String OscillatorModule::getOscType()
{
    return oscType;
}
