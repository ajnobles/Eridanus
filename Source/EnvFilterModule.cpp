/*
  ==============================================================================

    EnvFilterModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "EnvFilterModule.h"


EnvFilterModule::EnvFilterModule() 
{
    //
}


EnvFilterModule::~EnvFilterModule() 
{
    //
}


void EnvFilterModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR); 

    float x1 = OFFSET + THICKNESS,
          y1 = OFFSET + THICKNESS,
          x2 = this->getWidth() - (OFFSET + THICKNESS) * 1.0f,
          y2 = this->getHeight() - (OFFSET + THICKNESS) * 1.0f;

    Point <float> p1 = { x1, y1 };
    Point <float> p2 = { x2, y2 };

    Rectangle <float> border (p1, p2);
    
    g.drawRoundedRectangle (border, CORNERSIZE, THICKNESS);

    // TEMP IDENTIFICATION TEXT
    g.drawText ("EnvFILTER", 0, 0, getWidth(), getHeight(), Justification::centred); 

}



void EnvFilterModule::resized ()
{
    // 
}
