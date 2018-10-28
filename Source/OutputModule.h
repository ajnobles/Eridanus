/*
  ==============================================================================

    OutputModule.h
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"
   
// OUTPUT
class OutputModule : public CustomComponent
{
public:
    OutputModule (Slider* os, Slider* ofs,
                  Label* ol,  Label* ofl)
                : OutputSlider ( os ),
                  OutputFeedbackSlider ( ofs ),
                  OutputSliderLabel (ol),
                  OutputFeedbackLabel (ofl)
    {
        //
        addAndMakeVisible ( OutputSlider );
        OutputSlider->setRange ( 0, 100, 0 );
        OutputSlider->setSliderStyle (Slider::LinearVertical);
        OutputSlider->setTextBoxStyle (Slider::TextBoxBelow, true, 50, 20);

        addAndMakeVisible ( OutputFeedbackSlider );
        OutputFeedbackSlider->setRange ( 0.0, 100.0, 1.0 );
        OutputFeedbackSlider->setSliderStyle ( Slider::LinearBarVertical );
        OutputFeedbackSlider->setTextBoxStyle (Slider::NoTextBox, false, 0, 0);
        OutputFeedbackSlider->setValue (50.0f);


    }
    
    void paint (Graphics& g) override
    {
        g.setColour (BORDER_COLOR);

        CustomComponent::buildModuleBorder( g, CORNERSIZE, THICKNESS, OFFSET );
        // TEMP IDENTIFICATION TEXT
        g.drawText ("OUTPUT", 0, 25, getWidth(), getHeight(), Justification::centredTop); 

    }
    
    void resized () override
    {

        Grid grid;

        using Track = Grid::TrackInfo;

        grid.templateRows = { Track (1_fr), Track (10_fr) };
        grid.templateColumns = { Track (1_fr) , Track (1_fr) };

        grid.items = {
            GridItem ( nullptr ),
            GridItem ( nullptr ),
            GridItem ( OutputSlider ),
            GridItem ( OutputFeedbackSlider )
        };

        Rectangle<int> bounds = getLocalBounds();

        bounds = moduleInternalsBounds ( bounds, MODULE_INSIDE_OFFSET, OFFSET, THICKNESS );

        grid.performLayout ( bounds );
    }

private:
    Slider* OutputSlider;
    Label* OutputSliderLabel;

    Slider* OutputFeedbackSlider;
    Label* OutputFeedbackLabel;

};
