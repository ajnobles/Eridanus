/*
  ==============================================================================

    KeyboardScene.cpp
    Created: 26 Oct 2018 6:52:51am
    Author:  allen

  ==============================================================================
*/

#include "KeyboardScene.h"

KeyboardScene::KeyboardScene ()
{
    return;
}

KeyboardScene::~KeyboardScene ()
{
    return;
}

void KeyboardScene::paint ( Graphics& g )
{
    g.setColour ( BORDER_COLOR );
    g.drawText ( "KEYBOARD", 0, 0, getWidth(), getHeight(), Justification::centred );
}

void KeyboardScene::resized ()
{
    return;
}
