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
// Color pair for fundamentals
#define PAIR_FUNDAMENTAL 1
// Color pair for config
#define PAIR_CONFIG      2

Observer::Observer( double harmTol )
: mHarmonicTolerance( harmTol ),
  mWidth( 0 ),
  mHeight( 0 )
{
    // Load screen width and height
    getmaxyx( stdscr, mHeight, mWidth );

    // Start colors
    ::start_color();

    // Use default colors as -1
    ::use_default_colors();

    // Init color pairs
    ::init_pair( PAIR_FUNDAMENTAL, COLOR_RED, -1 );
    ::init_pair( PAIR_CONFIG, COLOR_YELLOW, -1 );
}

Observer::~Observer()
{
}

void Observer::start()
{
    // Wipe the screen
    ::clear();

    // Print config
    printConfig( mHeight - 6, "Device:             ", sConfigMgr[ "cgt.pcm.device" ] );
    printConfig( mHeight - 5, "Rate:               ", sConfigMgr[ "cgt.pcm.rate" ] );
    printConfig( mHeight - 4, "Buffer size:        ", sConfigMgr[ "cgt.bufferSize" ] );
    printConfig( mHeight - 3, "Capture size:       ", sConfigMgr[ "cgt.captureSize" ] );
    printConfig( mHeight - 2, "Magnitude cutoff:   ", sConfigMgr[ "cgt.fft.magnitudeCutoff" ] );
    printConfig( mHeight - 1, "Harmonic tolerance: ", sConfigMgr[ "cgt.fft.harmonicTolerance" ] );

    // Move cursor to (0,0)
    ::move( 0, 0 );

    // Flush harmonics.
    mFundamentals.clear();
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

void Observer::end()
{
    // Print the buffer
    ::refresh();
}

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
        if( harmonicTolerance() > 10 * ::log10( ::fabs( ratio - k ) ) )
            return k - 1;
    }

    // Add a new fundamental.
    mFundamentals.push_back( freq );
    return 0;
}

void Observer::printConfig( int line, const char* title, const char* value )
{
    // Move the cursor to position
    ::move( line, mWidth - 40 );

    // Turn on the color
    ::attron( COLOR_PAIR( PAIR_CONFIG ) );

    // Turn on bold
    ::attron( A_BOLD );
    // Print title
    ::addstr( title );
    // Turn off bold
    ::attroff( A_BOLD );

    // Print value
    ::addstr( value );

    // Turn off the color
    ::attroff( COLOR_PAIR( PAIR_CONFIG ) );
}
