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


    class Octave : public CustomComponent 
    {
    public:
        Octave();
        ~Octave();

        void paint ( Graphics& g ) override;
        void resized () override;


        class WhiteKey : public Keys 
        {
        public:
            WhiteKey();
            ~WhiteKey();

            void paint ( Graphics& g );
            void resized () override;

        private:
            TextButton whiteKey;
        };
 

        class BlackKey : public Keys
        {
        public:
            BlackKey();
            ~BlackKey();

            void paint ( Graphics& g );
            void resized () override;

        private:
            TextButton blackKey;
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
    };

   
private:

    Octave* lower;
    Octave* upper;

};
