/*
  ==============================================================================

    Utilities.h
    Created: 16 Oct 2018 11:07:40am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "CustomComponent.h"


//==============================================================================
/*
*/
class GUIUtilities    : public CustomComponent
{
public:
    GUIUtilities();
    ~GUIUtilities();

    void paint (Graphics&) override;
    void resized() override;


    class Selectors : public CustomComponent
    {
    public:
        Selectors();
        ~Selectors();
        void paint (Graphics&) override;
        void resized () override;
    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Selectors);
    };

private:

    Selectors Presets;
    Selectors MidiChannel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (GUIUtilities)
};
