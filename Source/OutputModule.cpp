/*
  ==============================================================================

    OutputModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "OutputModule.h"


OutputModule::OutputModule() 
{
    //
    
    addAndMakeVisible ( OutputSlider );
    OutputSlider.setRange ( 0, 100 );
    OutputSlider.setSliderStyle (Slider::LinearVertical);
    OutputSlider.setTextBoxStyle (Slider::TextBoxBelow, true, 50, 20);

}


OutputModule::~OutputModule() 
{
    //
}


void OutputModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR);

    CustomComponent::buildModuleBorder( g, CORNERSIZE, THICKNESS, OFFSET );
    // TEMP IDENTIFICATION TEXT
    g.drawText ("OUTPUT", 0, 0, getWidth(), getHeight(), Justification::centred); 

}



void OutputModule::resized ()
{
    OutputSlider.setBounds (0, 20, getWidth(), getHeight() - 50 ); 
}
