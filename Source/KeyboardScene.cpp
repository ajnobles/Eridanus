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
     
    lower = new Octave();
    addAndMakeVisible( lower );

    upper = new Octave();
    addAndMakeVisible( upper );
}


KeyboardScene::~KeyboardScene ()
{
    delete lower;
    delete upper;
}

void KeyboardScene::paint ( Graphics& g )
{
    g.setColour ( BORDER_COLOR );
}

void KeyboardScene::resized ()
{
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { 
        Track (1_fr)
    };
    
    grid.templateColumns = { 
        Track (1_fr), 
        Track (1_fr)
    };

    grid.autoColumns = Track (1_fr);

    grid.setGap( 10_px );


    grid.items = {
        GridItem ( lower ),
        GridItem ( upper )
    };

    Rectangle <int> bounds = getLocalBounds();


    bounds = moduleInternalsBounds ( bounds,
                                     MODULE_INSIDE_OFFSET,
                                     OFFSET,
                                     THICKNESS);


    grid.performLayout( bounds );
}






KeyboardScene::Octave::Octave()
{
    c1 = new WhiteKey();
    d1 = new WhiteKey();
    e1 = new WhiteKey();
    f1 = new WhiteKey();
    g1 = new WhiteKey();
    a2 = new WhiteKey();
    b2 = new WhiteKey();
 
    cSharp1 = new BlackKey();
    dSharp1 = new BlackKey();
    fSharp1 = new BlackKey();
    gSharp1 = new BlackKey();
    aSharp2 = new BlackKey();
 
    addAndMakeVisible( c1 );
    addAndMakeVisible( d1 );
    addAndMakeVisible( e1 );
    addAndMakeVisible( f1 );
    addAndMakeVisible( g1 );
    addAndMakeVisible( a2 );
    addAndMakeVisible( b2 );
 
    addAndMakeVisible( cSharp1 );
    addAndMakeVisible( dSharp1 );
    addAndMakeVisible( fSharp1 );
    addAndMakeVisible( gSharp1 );
    addAndMakeVisible( aSharp2 );
}


KeyboardScene::Octave::~Octave()
{
    delete c1;
    delete d1;
    delete e1;
    delete f1;
    delete g1;
    delete a2;
    delete b2;

    delete cSharp1;
    delete dSharp1;
    delete fSharp1;
    delete gSharp1;
    delete aSharp2;
}


void KeyboardScene::Octave::paint ( Graphics& g ) {}



void KeyboardScene::Octave::resized (  ) 
{
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { 
        Track (1_fr),
        Track (1_fr),
        Track (1_fr)
    };
    
    grid.templateColumns = { 
        Track (1_fr)
    };

    grid.autoColumns = Track (1_fr);

    grid.setGap( 10_px );


    grid.items = {
        GridItem ( c1      ).withArea( 1, 1,  4, 4 ),
        GridItem ( cSharp1 ).withArea( 1, 3,  3, 5 ),
        GridItem ( d1      ).withArea( 1, 4,  4, 7 ),
        GridItem ( dSharp1 ).withArea( 1, 6,  3, 8 ),
        GridItem ( e1      ).withArea( 1, 7,  4, 10 ),
        GridItem ( f1      ).withArea( 1, 10, 4, 13 ),
        GridItem ( fSharp1 ).withArea( 1, 12, 3, 14 ),
        GridItem ( g1      ).withArea( 1, 13, 4, 16 ),
        GridItem ( gSharp1 ).withArea( 1, 15, 3, 17 ),
        GridItem ( a2      ).withArea( 1, 16, 4, 19 ),
        GridItem ( aSharp2 ).withArea( 1, 18, 3, 20 ),
        GridItem ( b2      ).withArea( 1, 19, 4, 22 )
    };

    Rectangle <int> bounds = getLocalBounds();

    grid.performLayout ( bounds );
}




KeyboardScene::Octave::WhiteKey::WhiteKey()
{
    addAndMakeVisible( whiteKey );
    whiteKey.setColour( TextButton::buttonColourId, Colours::ivory );
    whiteKey.setColour( TextButton::buttonOnColourId, Colours::green );
}


KeyboardScene::Octave::WhiteKey::~WhiteKey()
{
}



void KeyboardScene::Octave::WhiteKey::paint ( Graphics& g )
{
    g.setColour( Colours::ivory );

    LookAndFeel_V4::drawButtonBackground( g, whiteKey, Colours::ivory, false, false );
}


void KeyboardScene::Octave::WhiteKey::resized ( )
{

    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = {
        Track (1_fr)
    };

    grid.templateColumns = {
        Track (1_fr)
    };

    
    grid.items = {
        GridItem ( whiteKey )
    };

    grid.performLayout( getLocalBounds() );

}




KeyboardScene::Octave::BlackKey::BlackKey()
{
    addAndMakeVisible( blackKey ); 
    blackKey.setColour( TextButton::buttonColourId, Colours::black );
    blackKey.setColour( TextButton::buttonOnColourId, Colours::green );

}


KeyboardScene::Octave::BlackKey::~BlackKey()
{
}



void KeyboardScene::Octave::BlackKey::paint ( Graphics& g )
{
    g.setColour( Colours::black );

    LookAndFeel_V4::drawButtonBackground( g, blackKey, Colours::black, false, false );

    // DRAW FILLED RECTANGLE
//    Rectangle <int> bounds = getLocalBounds();
//    bounds.setHeight( bounds.getHeight() * (2.0 / 3.0)  );
//    g.fillRect ( bounds );

}


void KeyboardScene::Octave::BlackKey::resized ( )
{
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows = {
        Track (1_fr)
    };

    grid.templateColumns = {
        Track (1_fr)
    };

    
    grid.items = {
        GridItem ( blackKey )
    };

    grid.performLayout( getLocalBounds() );

}
