/*
  ==============================================================================

    KeyboardScene.cpp
    Created: 26 Oct 2018 6:52:51am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"

class KeyboardScene : public CustomComponent
{
public:
    KeyboardScene ();
    ~KeyboardScene ();

    void paint ( Graphics& g ) override;
    void resized () override;
    
private:
};
