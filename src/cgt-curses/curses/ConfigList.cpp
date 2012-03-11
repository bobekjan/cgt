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
ConfigList::ConfigList( int xpos, int ypos, int width, int height )
: Window( xpos, ypos, width, height )
{
    // Init our color pair
    ::init_pair( PAIR_CONFIG, COLOR_YELLOW, -1 );

    // Draw a box
    box();
}

void ConfigList::refresh()
{
    // Print all lines
    addLine( 0, "Device:             ", sConfigMgr[ "cgt.pcm.device"            ] );
    addLine( 1, "Rate:               ", sConfigMgr[ "cgt.pcm.rate"              ] );
    addLine( 2, "Buffer size:        ", sConfigMgr[ "cgt.bufferSize"            ] );
    addLine( 3, "Capture size:       ", sConfigMgr[ "cgt.captureSize"           ] );
    addLine( 4, "Magnitude cutoff:   ", sConfigMgr[ "cgt.fft.magnitudeCutoff"   ] );
    addLine( 5, "Harmonic tolerance: ", sConfigMgr[ "cgt.fft.harmonicTolerance" ] );
    addLine( 6, "Tune tolerance:     ", sConfigMgr[ "cgt.tune.tolerance"        ] );
    addLine( 7, "Magnitude bar span: ", sConfigMgr[ "cgt.tune.magSpan"          ] );

    // Refresh the window
    Window::noutRefresh();
}

void ConfigList::addLine( int line, const char* title, const char* value )
{
    // Move the cursor to position (remember our border)
    move( 1 + line, 1 );

    // Turn on the color
    attrOn( A_BOLD | COLOR_PAIR( PAIR_CONFIG ) );

    // Print title
    addStr( title );

    // Turn off bold
    attrOff( A_BOLD );

    // Print value
    addStr( value );

    // Turn off the color
    attrOff( COLOR_PAIR( PAIR_CONFIG ) );
}
