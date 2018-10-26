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

OscillatorModule::~OscillatorModule() {}

void OscillatorModule::paint (Graphics& g)
{
    Colour colour = Colours::lightblue;
    String text = "OscillatorModule ITEM";
    g.fillAll (colour.withAlpha (0.5f));

    g.setColour (Colours::black);
    g.drawText (text, getLocalBounds().withSizeKeepingCentre (100, 100),
                    Justification::centred, false);
}
void OscillatorModule::resized ()
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
