/*
  ==============================================================================

    KeyboardScene.cpp
    Created: 26 Oct 2018 6:52:51am
    Author:  allen

  ==============================================================================
*/

#pragma once

#include "CustomComponent.h"
#include "Keys.h"

class KeyboardScene : public CustomComponent
{
public:
    KeyboardScene ();
    ~KeyboardScene ();

    void paint ( Graphics& g ) override;
    void resized () override;

    void buildOctave ();


    class WhiteKey : public Keys 
    {
    public:
        WhiteKey();
        ~WhiteKey();

        void paint ( Graphics& g );
        void resized () override;

    private:
    };
 

    class BlackKey : public Keys
    {
    public:
        BlackKey();
        ~BlackKey();

        void paint ( Graphics& g );
        void resized () override;

    private:
    };
    
private:

    WhiteKey* c1;
    BlackKey* cSharp1;
    WhiteKey* d1;
    BlackKey* dSharp1;
    WhiteKey* e1;
    WhiteKey* f1;
    BlackKey* fSharp1;
    WhiteKey* g1;
    BlackKey* gSharp1;
    WhiteKey* a2;
    BlackKey* aSharp2;
    WhiteKey* b2;

    WhiteKey* c2;
    BlackKey* cSharp2;
    WhiteKey* d2;
    BlackKey* dSharp2;
    WhiteKey* e2;
    WhiteKey* f2;
    BlackKey* fSharp2;
    WhiteKey* g2;
    BlackKey* gSharp2;
    WhiteKey* a3;
    BlackKey* aSharp3;
    WhiteKey* b3;
    WhiteKey* c3;
};
