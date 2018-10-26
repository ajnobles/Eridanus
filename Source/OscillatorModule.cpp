/*
  ==============================================================================

    OscillatorModule.cpp
    Created: 25 Oct 2018 7:09:22am
    Author:  allen

  ==============================================================================
*/

#include "OscillatorModule.h"

OscillatorModule::OscillatorModule (Slider* ls, Label* ll, Slider* fs, Label* fl, ComboBox *oB) 
    : levelSlider (ls), levelLabel (ll), freqSlider (fs) , freqLabel (fl), oscBox (oB)
{
    // LEVEL
    addAndMakeVisible ( levelSlider );
    levelSlider->setRange ( 0.0f, 0.5f );
    levelSlider->setTextBoxStyle ( Slider::TextBoxLeft, false, 50, 20 );
    levelSlider->setValue(0.0);
    levelSlider->setSliderStyle ( Slider::LinearHorizontal );
            
    addAndMakeVisible(levelLabel);
    levelLabel->setText("Osc Level", dontSendNotification);   
    
    // FREQ
    // frequency slider, slider display attributes
    addAndMakeVisible(freqSlider);
    freqSlider->setRange(200.0, 1000.0);
    freqSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
    freqSlider->setValue(440);
    freqSlider->setSliderStyle ( Slider::LinearHorizontal );
    
    //add frequency slider label and set text
    addAndMakeVisible(freqLabel);
    freqLabel->setText("Freq", dontSendNotification);
	        
    // COMBO BOX
    addAndMakeVisible(oscBox);
    oscBox->addItem("Sine", 1);
    oscBox->addItem("Saw", 2);
    oscBox->addItem("Square", 3);
    oscBox->addItem("Triangle", 4);
    oscBox->setSelectedId( 1 );    
}


OscillatorModule::~OscillatorModule() {}


void OscillatorModule::paint (Graphics& g)
{
    g.setColour ( BORDER_COLOR );
    buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );
}


void OscillatorModule::resized ()
{

    Rectangle <int> bounds = getLocalBounds();

    bounds = moduleInternalsBounds ( bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS );
    
    int x = bounds.getX(),
        y = bounds.getY(),
        width = bounds.getWidth(),
        height = bounds.getHeight();
    
    oscBox->setBounds ( x, y, width, height / 4 );
    
    levelSlider->setBounds ( x + 50, height * 0.75 / 2 * 1 + 10.0, width - 50, height / 4 );
    levelLabel ->setBounds ( x,      height * 0.75 / 2 * 1 + 10.0, 50,         height / 4 );
    
    freqSlider->setBounds  ( x + 50, height * 0.75 / 2 * 2 + 10.0, width - 50, height / 4 );
    freqLabel ->setBounds  ( x,      height * 0.75 / 2 * 2 + 10.0, 50,         height / 4 );    
}





