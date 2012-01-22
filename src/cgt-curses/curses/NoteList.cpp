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
NoteList::NoteList( int row, int col )
: mRow( row ),
  mCol( col )
{
    // Init our color pair
    ::init_pair( PAIR_FUNDAMENTAL, COLOR_RED, -1 );
}

void NoteList::add( double freq, unsigned int harm )
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
        ::attron( COLOR_PAIR( PAIR_FUNDAMENTAL ) );

    // Print it
#ifndef CGT_DEBUG_ANALYSIS_FREQ
    ::printw( "[%-*u] ", off, harm );

    ::attron( A_BOLD );
    ::printw( "%10s ", mName );
    ::attroff( A_BOLD );

    ::printw( "(%10.4f Hz)\n", freq );
#else /* !CGT_DEBUG_ANALYSIS_FREQ */
    ::printw( "[%-*u] ", off, harm );

    ::attron( A_BOLD );
    ::printw( "%10s ", mName );
    ::attroff( A_BOLD );

    ::printw( "(%10.4f Hz) = ", freq );

    ::attron( A_BOLD );
    ::printw( "%10.4f dB\n", 10 * ::log10( ::fabs( freq - CGT_DEBUG_ANALYSIS_FREQ ) ) );
    ::attroff( A_BOLD );
#endif /* !CGT_DEBUG_ANALYSIS_FREQ */

    if( 0 == harm )
        // Fundamental, turn off color
        ::attroff( COLOR_PAIR( PAIR_FUNDAMENTAL ) );
}

void NoteList::clear()
{
    // Move cursor to the default position
    ::move( mRow, mCol );
}
