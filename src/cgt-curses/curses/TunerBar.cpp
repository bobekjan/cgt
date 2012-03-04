/**
 * @file curses/TunerBar.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/TunerBar.h"

using namespace cgt::curses;

/*************************************************************************/
/* cgt::curses::TunerBar                                                 */
/*************************************************************************/
TunerBar::TunerBar( int xpos, int ypos, int width, int height )
: Window( xpos, ypos, width, height ),
  mTuneTolerance( sConfigMgr[ "cgt.tune.tolerance" ] )
{
    // Initialize our color pair
    ::init_pair( PAIR_TUNER_GOOD, COLOR_GREEN,  -1 );
    ::init_pair( PAIR_TUNER_BAD,  COLOR_RED,    -1 );
    ::init_pair( PAIR_TUNER_DESC, COLOR_YELLOW, -1 );
}

void TunerBar::add( const util::Tone& tone )
{
    // Obtain name of the note
    char name[ 0x20 ];
    tone.getName( name, sizeof( name ) );

    // Obtain min and max frequencies
    const util::Tone toneMin( tone.note(), -50, tone.octave() );
    const util::Tone toneMax( tone.note(), +50, tone.octave() );

    // Determine exactness
    const bool exact = ( ::fabs( tone.cents() ) <= mTuneTolerance );

    // Clear the window
    Window::erase();

    // Get width & height
    int width, height;
    getmaxyx( mWindow, height, width );

    // Draw background
    mvwhline( mWindow, height - 6, 1, '-', width - 2 );
    mvwhline( mWindow, height - 5, 1, '-', width - 2 );
    mvwhline( mWindow, height - 4, 1, '-', width - 2 );
    mvwhline( mWindow, height - 3, 1, '-', width - 2 );

    // Locate the marker
    int mark = 1.5 + ( width - 3 )
        * ( tone.frequency()    - toneMin.frequency() )
        / ( toneMax.frequency() - toneMin.frequency() );

    // Draw the colorized markers
    attrOn( COLOR_PAIR( exact ? PAIR_TUNER_GOOD : PAIR_TUNER_BAD ) );

    mvwvline( mWindow, height - 6, mark, '|', 4 );

    mvwhline( mWindow, height / 4 - 1, ( width - 9 ) / 2, ACS_BLOCK, 9 );
    mvwhline( mWindow, height / 4    , ( width - 9 ) / 2, ACS_BLOCK, 9 );
    mvwhline( mWindow, height / 4 + 1, ( width - 9 ) / 2, ACS_BLOCK, 9 );

    attrOff( COLOR_PAIR( exact ? PAIR_TUNER_GOOD : PAIR_TUNER_BAD ) );

    attrOn( A_BOLD | COLOR_PAIR( PAIR_TUNER_DESC ) );

    // Draw arrows
    if( 0 > tone.cents() )
        mvwhline( mWindow, height / 4, 3 * width / 4 - 2, ACS_RARROW, 4 );
    else
        mvwhline( mWindow, height / 4, 1 * width / 4 - 2, ACS_LARROW, 4 );

    // Print note name
    mvwaddstr( mWindow, height / 2, ( width - ::strlen( name ) ) / 2, name );

    attrOff( A_BOLD | COLOR_PAIR( PAIR_TUNER_DESC ) );
}

void TunerBar::refresh()
{
    // Get width & height
    int width, height;
    getmaxyx( mWindow, height, width );

    // Draw little borders
    mvwvline( mWindow, height - 6,         0, '[', 4 );
    mvwvline( mWindow, height - 6, width - 1, ']', 4 );

    // Refresh content of the window
    Window::noutRefresh();
    // Clear the window
    Window::erase();
}
