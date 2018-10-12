/*
  ==============================================================================

    CustomComponent.h
    Created: 12 Oct 2018 3:43:03pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

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
