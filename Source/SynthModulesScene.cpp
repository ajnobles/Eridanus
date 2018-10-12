/*
  ==============================================================================

    SynthModulesScene.cpp
    Created: 12 Oct 2018 11:28:14am
    Author:  allen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SynthModulesScene.h"

//==============================================================================
SynthModulesScene::SynthModulesScene()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

SynthModulesScene::~SynthModulesScene()
{
}

void SynthModulesScene::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    // g.fillAll (Colours::lightblue);
    

    // BUILD SYNTH MODULE BORDER
    g.setColour (Colours::white);

    float cornerSize  = 20.0f,
          thickness   = 10.0f,
          offset      = 5.0f;
/*
    float rectX = offset + thickness,
          rectY = offset + thickness,
          width = getWidth() - (offset + thickness) * 2.0f,
          height = getHeight() - (offset + thickness) * 2.0f;

    Rectangle<float> border { rectX,
                              rectY,
                              width,
                              height };

    g.drawRoundedRectangle (border, cornerSize, thickness); 
*/
    buildBorder (g, cornerSize, thickness, offset);


    g.setFont (Font (16.0f));
    g.setColour (Colours::red);
    g.drawText ("SYNTH MODULES", getLocalBounds(), Justification::centred, true);
}

void SynthModulesScene::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void SynthModulesScene::buildBorder(Graphics& g, float cornerSize, float thickness, float offset)
{
    float rectX = offset + thickness,
          rectY = offset + thickness,
          width = getWidth() - (offset + thickness) * 2.0f,
          height = getHeight() - (offset + thickness) * 2.0f;

    Rectangle<float> border { rectX,
                              rectY,
                              width,
                              height };

    g.drawRoundedRectangle (border, cornerSize, thickness); 
}
