/*
  ==============================================================================

    CustomComponent.cpp
    Created: 12 Oct 2018 3:43:03pm
    Author:  allen

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"

//==============================================================================
CustomComponent::CustomComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}

CustomComponent::~CustomComponent()
{
}

void CustomComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

}

void CustomComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void CustomComponent::buildRoundedRectangle(Graphics& g, float cornerSize, float thickness, float offset)
{
    float x = offset + thickness,
          y = offset + thickness,
          width = getWidth() - (offset + thickness) * 2.0f,
          height = getHeight() - (offset + thickness) * 2.0f;

    Rectangle <float> border { x,
                               y,
                               width,
                               height };

    g.drawRoundedRectangle (border, cornerSize, thickness);
}
