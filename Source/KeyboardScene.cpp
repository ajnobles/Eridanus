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
   
    c2 = new WhiteKey();
    d2 = new WhiteKey();
    e2 = new WhiteKey();
    f2 = new WhiteKey();
    g2 = new WhiteKey();
    a3 = new WhiteKey();
    b3 = new WhiteKey();
    c3 = new WhiteKey();
  
    cSharp2 = new BlackKey();
    dSharp2 = new BlackKey();
    fSharp2 = new BlackKey();
    gSharp2 = new BlackKey();
    aSharp3 = new BlackKey();

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

    addAndMakeVisible( c2 );
    addAndMakeVisible( d2 );
    addAndMakeVisible( e2 );
    addAndMakeVisible( f2 );
    addAndMakeVisible( g2 );
    addAndMakeVisible( a3 );
    addAndMakeVisible( b3 );
    addAndMakeVisible( c3 );

    addAndMakeVisible( cSharp2 );
    addAndMakeVisible( dSharp2 );
    addAndMakeVisible( fSharp2 );
    addAndMakeVisible( gSharp2 );
    addAndMakeVisible( aSharp3 );

}

KeyboardScene::~KeyboardScene ()
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

    delete c2;
    delete d2;
    delete e2;
    delete f2;
    delete g2;
    delete a3;
    delete b3;
    delete c3;

    delete cSharp2;
    delete dSharp2;
    delete fSharp2;
    delete gSharp2;
    delete aSharp3;
}

void KeyboardScene::paint ( Graphics& g )
{
    g.setColour ( BORDER_COLOR );
    g.drawText ( "KEYBOARD", 0, 25, getWidth(), getHeight(), Justification::centredTop );
}

void KeyboardScene::resized ()
{
    Grid grid;

    using Track = Grid::TrackInfo;

    grid.templateRows    = { 
        Track (1_fr)
    };
    
    grid.templateColumns = { 
        Track (1_fr)
    };

    grid.autoColumns = Track (1_fr);

    grid.setGap( 10_px );


    grid.items = {

        GridItem ( c1      ).withArea( 1, 1,  1, 4 ),
        GridItem ( cSharp1 ).withArea( 1, 3,  1, 5 ),
        GridItem ( d1      ).withArea( 1, 4,  1, 7 ),
        GridItem ( dSharp1 ).withArea( 1, 6,  1, 8 ),
        GridItem ( e1      ).withArea( 1, 7,  1, 10 ),
        GridItem ( f1      ).withArea( 1, 10, 1, 13 ),
        GridItem ( fSharp1 ).withArea( 1, 12, 1, 14 ),
        GridItem ( g1      ).withArea( 1, 13, 1, 16 ),
        GridItem ( gSharp1 ).withArea( 1, 15, 1, 17 ),
        GridItem ( a2      ).withArea( 1, 16, 1, 19 ),
        GridItem ( aSharp2 ).withArea( 1, 18, 1, 20 ),
        GridItem ( b2      ).withArea( 1, 19, 1, 22 ),
 
        GridItem ( c2      ).withArea( 1, 22, 1, 25 ),
        GridItem ( cSharp2 ).withArea( 1, 24, 1, 26 ),
        GridItem ( d2      ).withArea( 1, 25, 1, 28 ),
        GridItem ( dSharp2 ).withArea( 1, 27, 1, 29 ),
        GridItem ( e2      ).withArea( 1, 28, 1, 31 ),
        GridItem ( f2      ).withArea( 1, 31, 1, 34 ),
        GridItem ( fSharp2 ).withArea( 1, 33, 1, 35 ),
        GridItem ( g2      ).withArea( 1, 34, 1, 37 ),
        GridItem ( gSharp2 ).withArea( 1, 36, 1, 38 ),
        GridItem ( a3      ).withArea( 1, 37, 1, 40 ),
        GridItem ( aSharp3 ).withArea( 1, 39, 1, 41 ),
        GridItem ( b3      ).withArea( 1, 40, 1, 43 ),
        GridItem ( c3      ).withArea( 1, 43, 1, 46 )
       
    };

    Rectangle <int> bounds = getLocalBounds();

    // bounds.setWidth( bounds.getWidth() );

    bounds = moduleInternalsBounds ( bounds,
                                     MODULE_INSIDE_OFFSET,
                                     OFFSET,
                                     THICKNESS);

    grid.performLayout( bounds );
}












KeyboardScene::WhiteKey::WhiteKey()
{
}


KeyboardScene::WhiteKey::~WhiteKey()
{
}



void KeyboardScene::WhiteKey::paint ( Graphics& g )
{
    g.setColour( Colours::ivory );

    // DRAW FILLED RECTANGLE
    g.fillRect ( getLocalBounds() );
}


void KeyboardScene::WhiteKey::resized ( )
{
}




KeyboardScene::BlackKey::BlackKey()
{
}


KeyboardScene::BlackKey::~BlackKey()
{
}



void KeyboardScene::BlackKey::paint ( Graphics& g )
{
    g.setColour( Colours::black );

    // DRAW FILLED RECTANGLE
    Rectangle <int> bounds = getLocalBounds();
    bounds.setHeight( bounds.getHeight() * (2.0 / 3.0)  );
    g.fillRect ( bounds );

}


void KeyboardScene::BlackKey::resized ( )
{
}
