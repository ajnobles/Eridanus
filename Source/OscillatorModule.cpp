/*
  ==============================================================================

    OscillatorModule.cpp
    Created: 25 Oct 2018 7:09:22am
    Author:  allen

  ==============================================================================
*/

#include "OscillatorModule.h"

OscillatorModule::OscillatorModule (Slider* ls, ComboBox *lB, Slider* fts, Slider* fs, ComboBox *oB) 
    : levelSlider (ls), lengthBox (lB), fineTuneSlider (fts),  freqSlider (fs),  oscBox (oB)
{
    // LEVEL
    addAndMakeVisible ( levelSlider );
    levelSlider->setRange ( 0.0f, 0.3f );
    levelSlider->setTextBoxStyle ( Slider::TextBoxRight, false, 50, 20 );
    levelSlider->setValue(0.0);
            
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Osc Output", dontSendNotification);   
    
    // FREQ
    // frequency slider, slider display attributes
    addAndMakeVisible(freqSlider);
    freqSlider->setRange(200.0, 1000.0);
    freqSlider->setTextBoxStyle(Slider::TextBoxRight, false, 50, 20);
    freqSlider->setValue(400);
    
    addAndMakeVisible(freqLabel);
    freqLabel.setText("Osc Freq", dontSendNotification);
    
    // FINE TUNE
    addAndMakeVisible(fineTuneSlider);
    fineTuneSlider->setRange(-1.0, 1.0);
    fineTuneSlider->setTextBoxStyle(Slider::TextBoxRight, false, 50, 20);
    fineTuneSlider->setValue(0.0);
    
    addAndMakeVisible(fineTune);
    fineTune.setText("Fine Tune", dontSendNotification);
    
    // OSC COMBO BOX
    addAndMakeVisible(oscBox);
    oscBox->addItem("Sine", 1);
    oscBox->addItem("Saw", 2);
    oscBox->addItem("Square", 3);
    oscBox->addItem("Triangle", 4);
    
    addAndMakeVisible(oscType);
    oscType.setText("Osc Type", dontSendNotification);
    
    // LENGTH COMBO BOX
    addAndMakeVisible(lengthBox);
    lengthBox->addItem("4", 1);
    lengthBox->addItem("8", 2);
    lengthBox->addItem("16", 3);
    
    addAndMakeVisible(oscLength);
    oscLength.setText("Osc Length", dontSendNotification);
}

OscillatorModule::~OscillatorModule() {}

void OscillatorModule::paint (Graphics& g)
{
    Colour colour = Colours::lightblue;
    //String text = "OscillatorModule ITEM";
    String text = " ";
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
    grid.templateColumns = { Track (1_fr), Track (3_fr) };
  
    grid.autoRows = Track (1_fr);
    grid.autoColumns = Track (1_fr);

    grid.items = {
        GridItem ( oscType      ),
        GridItem ( oscBox       ),
        GridItem ( oscLength    ),
        GridItem ( lengthBox    ),
        GridItem ( fineTune     ),
        GridItem ( fineTuneSlider),
        GridItem ( levelLabel   ),
        GridItem ( levelSlider  ),
        GridItem ( freqLabel    ),
        GridItem ( freqSlider   )
    };

    grid.performLayout ( getLocalBounds() );
}
