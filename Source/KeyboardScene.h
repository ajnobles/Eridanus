/*
  ==============================================================================

    KeyboardScene.h
    Created: 12 Oct 2018 12:38:56pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class KeyboardScene    : public Component
{
public:
    KeyboardScene();
    ~KeyboardScene();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardScene)
};
