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

    void fillFrequecyVector();
    float getBaseFrequency();
    void  setBaseFrequency( float v );
    vector<float> getOctaveFrequencies( int octave );


    class Octave : public CustomComponent 
    {
    public:
        Octave( vector<float> frequencies );
        ~Octave();

        void paint ( Graphics& g ) override;
        void resized () override;


        class WhiteKey : public Keys 
        {
        public:
            WhiteKey( float freq );
            ~WhiteKey();

            void paint ( Graphics& g );
            void resized () override;

            float getFrequency();

        private:
            TextButton whiteKey;
            float frequency;
        };
 

        class BlackKey : public Keys
        {
        public:
            BlackKey( float freq );
            ~BlackKey();

            void paint ( Graphics& g );
            void resized () override;

            float getFrequency();

        private:
            TextButton blackKey;
            float frequency;
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

    float baseFrequency;
    // HOLDS FREQUENCIES FROM C0 thru B7
    vector< vector<float> > key_frequencies;

};
