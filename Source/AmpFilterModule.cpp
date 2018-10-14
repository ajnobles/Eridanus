/*
  ==============================================================================

    AmpFilterModule.cpp
    Created: 12 Oct 2018 4:19:38pm
    Author:  allen

  ==============================================================================
*/

#include "AmpFilterModule.h"


AmpFilterModule::AmpFilterModule() 
{
    //
}


AmpFilterModule::~AmpFilterModule() 
{
    //
}


void AmpFilterModule::paint (Graphics& g)
{
    g.setColour (BORDER_COLOR);
    buildModuleBorder (g, CORNERSIZE, THICKNESS, OFFSET);

    // TEMP IDENTIFICATION TEXT
    g.drawText ("AmpFILTER", 0, 0, getWidth(), getHeight(), Justification::centred); 
}



void AmpFilterModule::resized ()
{
    // 
}
