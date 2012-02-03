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
: Window( row, col, 40, 8 )
{
    // Init our color pair
    ::init_pair( PAIR_CONFIG, COLOR_YELLOW, -1 );
}

void ConfigList::refresh()
{
    // Print all lines
    print( 0, "Device:             ", sConfigMgr[ "cgt.pcm.device" ] );
    print( 1, "Rate:               ", sConfigMgr[ "cgt.pcm.rate" ] );
    print( 2, "Buffer size:        ", sConfigMgr[ "cgt.bufferSize" ] );
    print( 3, "Capture size:       ", sConfigMgr[ "cgt.captureSize" ] );
    print( 4, "Magnitude cutoff:   ", sConfigMgr[ "cgt.fft.magnitudeCutoff" ] );
    print( 5, "Harmonic tolerance: ", sConfigMgr[ "cgt.fft.harmonicTolerance" ] );

    // Draw a box
    box();

    // Refresh the window
    Window::refresh();
}

void ConfigList::print( int line, const char* title, const char* value )
{
    // Move the cursor to position (remember our border)
    move( 1 + line, 1 );

    // Turn on the color
    attrOn( COLOR_PAIR( PAIR_CONFIG ) );

    // Turn on bold
    attrOn( A_BOLD );
    // Print title
    addStr( title );
    // Turn off bold
    attrOff( A_BOLD );

    // Print value
    addStr( value );

    // Turn off the color
    attrOff( COLOR_PAIR( PAIR_CONFIG ) );
}
