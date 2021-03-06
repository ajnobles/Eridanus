/*
  ==============================================================================

    KeyboardScene.h
    Created: 12 Oct 2018 12:38:56pm
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "CustomComponent.h"

//==============================================================================
/*
*/
class KeyboardModuleScene    : public CustomComponent
{
public:
    KeyboardModuleScene();
    ~KeyboardModuleScene();

    void paint (Graphics&) override;
    void resized() override;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardModuleScene)
};
