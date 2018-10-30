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
// <<<<<<< Integration_10_29_18
    levelSlider->setRange ( 0.0f, 0.3f );
    levelSlider->setTextBoxStyle ( Slider::TextBoxRight, false, 50, 20 );
    levelSlider->setValue(0.0);
// =======
    // levelSlider->setRange ( 0.0f, 0.5f );
    // levelSlider->setTextBoxStyle ( Slider::TextBoxLeft, false, 50, 20 );
    // levelSlider->setValue(0.0);
    levelSlider->setSliderStyle ( Slider::LinearHorizontal );
// >>>>>>> Allen_Gui_Main
            
    addAndMakeVisible(levelLabel);
    levelLabel.setText("Osc Output", dontSendNotification);   
    
    // FREQ
    // frequency slider, slider display attributes
    addAndMakeVisible(freqSlider);
    freqSlider->setRange(200.0, 1000.0);
// <<<<<<< Integration_10_29_18
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
// =======
    // freqSlider->setTextBoxStyle(Slider::TextBoxLeft, false, 50, 20);
    // freqSlider->setValue(440);
    freqSlider->setSliderStyle ( Slider::LinearHorizontal );
    
    //add frequency slider label and set text
    // addAndMakeVisible(freqLabel);
    // freqLabel->setText("Freq", dontSendNotification);
	        
    // COMBO BOX
// >>>>>>> Allen_Gui_Main
    addAndMakeVisible(oscBox);
    oscBox->addItem("Sine", 1);
    oscBox->addItem("Saw", 2);
    oscBox->addItem("Square", 3);
    oscBox->addItem("Triangle", 4);
// <<<<<<< Integration_10_29_18
    
    addAndMakeVisible(oscType);
    oscType.setText("Osc Type", dontSendNotification);
    
    // LENGTH COMBO BOX
    addAndMakeVisible(lengthBox);
    lengthBox->addItem("4", 1);
    lengthBox->addItem("8", 2);
    lengthBox->addItem("16", 3);
    
    addAndMakeVisible(oscLength);
    oscLength.setText("Osc Length", dontSendNotification);
// =======
    oscBox->setSelectedId( 1 );    
// >>>>>>> Allen_Gui_Main
}


OscillatorModule::~OscillatorModule() {}


void OscillatorModule::paint (Graphics& g)
{
// <<<<<<< Integration_10_29_18
    Colour colour = Colours::lightblue;
    //String text = "OscillatorModule ITEM";
    String text = " ";
    g.fillAll (colour.withAlpha (0.5f));

    g.setColour (Colours::black);
    g.drawText (text, getLocalBounds().withSizeKeepingCentre (100, 100),
                    Justification::centred, false);
// =======
    // g.setColour ( BORDER_COLOR );
    // buildModuleBorder ( g, CORNERSIZE, THICKNESS, OFFSET );
// >>>>>>> Allen_Gui_Main
}


void OscillatorModule::resized ()
{
// <<<<<<< Integration_10_29_18
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
// =======
/*
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
*/
// >>>>>>> Allen_Gui_Main
}





