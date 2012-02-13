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
: Window( xpos, ypos, width, height )
{
    // Initialize our color pair
    ::init_pair( PAIR_TUNER_GOOD,  COLOR_GREEN,  -1 );
    ::init_pair( PAIR_TUNER_BAD,   COLOR_RED,    -1 );
    ::init_pair( PAIR_TUNER_ARROW, COLOR_YELLOW, -1 );
}

void TunerBar::add( double freq )
{
    // Obtain description of the note
    int octave;
    double cents;
    util::Note n = util::noteName( freq, octave, cents );

    // Obtain min and max frequencies
    double freqMin = util::noteFreq( n, octave, -50 );
    double freqMax = util::noteFreq( n, octave, +50 );

    // Determine exactness
    bool exact = ( 2.0 > ::fabs( cents ) );

    // Get width & height
    int width, height;
    getmaxyx( mWindow, height, width );

    // Draw background
    mvwhline( mWindow, height - 6, 1, '-', width - 2 );
    mvwhline( mWindow, height - 5, 1, '-', width - 2 );
    mvwhline( mWindow, height - 4, 1, '-', width - 2 );
    mvwhline( mWindow, height - 3, 1, '-', width - 2 );

    // Locate the marker
    int mark = 1.5 + ( width - 3 ) * ( freq - freqMin ) / ( freqMax - freqMin );

    // Draw the colorized markers
    attrOn( COLOR_PAIR( exact ? PAIR_TUNER_GOOD : PAIR_TUNER_BAD ) );

    mvwvline( mWindow, height - 6, mark, '|', 4 );

    mvwhline( mWindow, height / 4 - 1, ( width - 9 ) / 2, ACS_BLOCK, 9 );
    mvwhline( mWindow, height / 4    , ( width - 9 ) / 2, ACS_BLOCK, 9 );
    mvwhline( mWindow, height / 4 + 1, ( width - 9 ) / 2, ACS_BLOCK, 9 );

    attrOff( COLOR_PAIR( exact ? PAIR_TUNER_GOOD : PAIR_TUNER_BAD ) );

    // Draw arrows
    attrOn( A_BOLD | COLOR_PAIR( PAIR_TUNER_ARROW ) );

    if( 0 > cents )
        mvwhline( mWindow, height / 4, 3 * width / 4 - 2, ACS_RARROW, 4 );
    else
        mvwhline( mWindow, height / 4, 1 * width / 4 - 2, ACS_LARROW, 4 );

    attrOff( A_BOLD | COLOR_PAIR( PAIR_TUNER_ARROW ) );
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
    Window::refresh();
}

void TunerBar::clear()
{
    // Clear the window
    Window::clear();
}
