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

    float cornerSize = 0.0f,
          thickness  = 3.0f,
          offset     = 2.5f;

    float sizeX = 50.0f,
          sizeY = 125.0f;

    Point <float> p1 = { offset, offset };
    Point <float> p2 = { offset + sizeX, offset + sizeY };

    Rectangle <float> border (p1, p2);
    
    g.drawRoundedRectangle (border, cornerSize, thickness);

}



void OutputModule::resized ()
{
    // 
}
