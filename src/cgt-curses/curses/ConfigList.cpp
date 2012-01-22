/**
 * @file curses/ConfigList.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/ConfigList.h"

using namespace cgt;
using namespace cgt::curses;

/*************************************************************************/
/* cgt::curses::ConfigList                                               */
/*************************************************************************/
ConfigList::ConfigList( int row, int col )
: mRow( row ),
  mCol( col )
{
    // Init our color pair
    ::init_pair( PAIR_CONFIG, COLOR_YELLOW, -1 );
}

void ConfigList::print()
{
    print( mRow + 0, "Device:             ", sConfigMgr[ "cgt.pcm.device" ] );
    print( mRow + 1, "Rate:               ", sConfigMgr[ "cgt.pcm.rate" ] );
    print( mRow + 2, "Buffer size:        ", sConfigMgr[ "cgt.bufferSize" ] );
    print( mRow + 3, "Capture size:       ", sConfigMgr[ "cgt.captureSize" ] );
    print( mRow + 4, "Magnitude cutoff:   ", sConfigMgr[ "cgt.fft.magnitudeCutoff" ] );
    print( mRow + 5, "Harmonic tolerance: ", sConfigMgr[ "cgt.fft.harmonicTolerance" ] );
}

void ConfigList::print( int line, const char* title, const char* value )
{
    // Move the cursor to position
    ::move( line, mCol );

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
