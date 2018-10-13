/*
  ==============================================================================

    CustomComponent.h
    Created: 12 Oct 2018 3:43:03pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define CORNERSIZE 20.0f
#define THICKNESS  10.0f
#define OFFSET      5.0F

//==============================================================================
/*
*/
class CustomComponent    : public Component
{
public:
    CustomComponent();
    ~CustomComponent();

    void paint (Graphics&) override;
    void resized() override;

    void buildRoundedRectangle(Graphics& g, float cornerSize, float thickness, float offset);

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (CustomComponent)
};
