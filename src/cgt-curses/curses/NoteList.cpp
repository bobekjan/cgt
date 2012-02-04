/**
 * @file curses/NoteList.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/NoteList.h"

using namespace cgt;
using namespace cgt::curses;

/*************************************************************************/
/* cgt::curses::NoteList                                                 */
/*************************************************************************/
NoteList::NoteList( int xpos, int ypos )
: Window( xpos, ypos, 36, 15 )
{
    // Init our color pair
    ::init_pair( PAIR_FUNDAMENTAL, COLOR_RED, -1 );
}

void NoteList::print( double freq, unsigned int harm )
{
    // Obtain name of the note
    int octave;
    double cents;
    util::Note note = util::noteName( freq, octave, cents );

    // Generate the name
    util::noteStr( note, octave, cents,
                   mName, sizeof( mName ) );

    unsigned int off  = ::log2( harm + 1 ) + 1;

    if( 0 == harm )
        // Fundamental, turn on color
        attrOn( COLOR_PAIR( PAIR_FUNDAMENTAL ) );

    // Print it
#ifndef CGT_DEBUG_ANALYSIS_FREQ
    printw( " [%-*u] ", off, harm );

    attrOn( A_BOLD );
    printw( "%10s ", mName );
    attrOff( A_BOLD );

    printw( "(%10.4f Hz)\n", freq );
#else /* !CGT_DEBUG_ANALYSIS_FREQ */
    printw( "[%-*u] ", off, harm );

    attrOn( A_BOLD );
    printw( "%10s ", mName );
    attrOff( A_BOLD );

    printw( "(%10.4f Hz) = ", freq );

    attrOn( A_BOLD );
    printw( "%10.4f dB\n", 10 * ::log10( ::fabs( freq - CGT_DEBUG_ANALYSIS_FREQ ) ) );
    attrOff( A_BOLD );
#endif /* !CGT_DEBUG_ANALYSIS_FREQ */

    if( 0 == harm )
        // Fundamental, turn off color
        attrOff( COLOR_PAIR( PAIR_FUNDAMENTAL ) );
}

void NoteList::refresh()
{
    // Draw a box
    box();

    // Refresh content of the window
    Window::refresh();
}

void NoteList::clear()
{
    // Clear the window
    Window::clear();

    // Move cursor to the default position (remember our border)
    move( 1, 0 );
}
