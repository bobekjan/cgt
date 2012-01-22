/**
 * @file curses/Observer.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/Observer.h"

using namespace cgt::curses;

/*************************************************************************/
/* cgt::curses::Observer                                                 */
/*************************************************************************/
void Observer::start()
{
    // Wipe the screen
    ::clear();

    // Move cursor to (0,0)
    ::move( 0, 0 );

    // Flush harmonics.
    clearHarmonic();
}

void Observer::add( double freq )
{
    // Obtain name of the note
    int octave;
    double cents;
    util::Note note = util::noteName( freq, octave, cents );

    // Generate the name
    util::noteStr( note, octave, cents,
                   mName, sizeof( mName ) );

    // Obtain harmonic index
    unsigned int harm = getHarmonic( freq );

    // Print it
#ifndef CGT_DEBUG_ANALYSIS_FREQ
    ::printw( "[%-*u] ", (int)::log2( harm + 1 ) + 1, harm );

    ::attron( A_BOLD );
    ::printw( "%10s ", mName );
    ::attroff( A_BOLD );

    ::printw( "(%10.4f Hz)\n", freq );
#else /* !CGT_DEBUG_ANALYSIS_FREQ */
    ::printw( "[%-*u] ", (int)::log2( harm + 1 ) + 1, harm );

    ::attron( A_BOLD );
    ::printw( "%10s ", mName );
    ::attroff( A_BOLD );

    ::printw( "(%10.4f Hz) = ", freq );

    ::attron( A_BOLD );
    ::printw( "%10.4f dB\n", 10 * ::log10( ::fabs( freq - CGT_DEBUG_ANALYSIS_FREQ ) ) );
    ::attroff( A_BOLD );
#endif /* !CGT_DEBUG_ANALYSIS_FREQ */
}

void Observer::end()
{
    // Print the buffer
    ::refresh();
}

#ifdef CGT_DEBUG_ANALYSE_HARMONICS
unsigned int Observer::getHarmonic( double freq )
{
    std::vector< double >::const_iterator cur, end;
    cur = mFundamentals.begin();
    end = mFundamentals.end();
    for(; cur != end; ++cur )
    {
        // Calculate ratio of the frequencies.
        double ratio = freq / *cur;
        // Round it to the nearest integer.
        int k = ratio + 0.5;

        // If the error is small enough, return the ratio.
        if( -9.0 > 10 * ::log10( ::fabs( ratio - k ) ) )
            return k - 1;
    }

    // Add a new fundamental.
    mFundamentals.push_back( freq );
    return 0;
}

void Observer::clearHarmonic()
{
    mFundamentals.clear();
}
#endif /* CGT_DEBUG_ANALYSE_HARMONICS */
