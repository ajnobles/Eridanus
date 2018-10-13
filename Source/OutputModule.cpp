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
}


OutputModule::~OutputModule() 
{
    //
}


void OutputModule::paint (Graphics& g)
{
    g.setColour (Colours::yellow);

    float x1 = OFFSET + THICKNESS,
          y1 = OFFSET + THICKNESS,
          x2 = this->getWidth() - (OFFSET + THICKNESS) * 1.0f,
          y2 = this->getHeight() - (OFFSET + THICKNESS) * 1.0f;

    Point <float> p1 = { x1, y1 };
    Point <float> p2 = { x2, y2 };

    Rectangle <float> border (p1, p2);
    
    g.drawRoundedRectangle (border, CORNERSIZE, THICKNESS);

}



void OutputModule::resized ()
{
    // 
}
