/**
 * @file curses/MagnitudeBar.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/MagnitudeBar.h"

using namespace cgt::curses;

/*************************************************************************/
/* cgt::curses::MagnitudeBar                                             */
/*************************************************************************/
MagnitudeBar::MagnitudeBar( int xpos, int ypos, int width, int height )
: Window( xpos, ypos, width, height ),
  mCutoff( sConfigMgr[ "cgt.fft.magnitudeCutoff" ] )
{
    // Init our colors
    ::init_pair( PAIR_MAGBAR, COLOR_WHITE, -1 );
}

void MagnitudeBar::add( double mag )
{
    // Pass it to maximum.
    mMax.add( mag );
}

void MagnitudeBar::refresh()
{
    // Draw a box
    box();

    // Check if the counter is ready
    if( mMax.ready() )
    {
        // Obtain the maximum
        double mag = 10 * ::log10( mMax.result() );
        double span = 12;

        int width, height;
        getmaxyx( mWindow, height, width );

        // Calculate bar
        int bar = ( height - 2 ) * ( mag - mCutoff ) / span;
        bar = std::min( bar, height - 2 );

        // Print the colorized bar
        attrOn( COLOR_PAIR( PAIR_MAGBAR ) );
        mvwvline( mWindow, height - bar - 1, 1, '*', bar );
        attrOff( COLOR_PAIR( PAIR_MAGBAR ) );
    }

    // Refresh content of the window
    Window::refresh();
}

void MagnitudeBar::clear()
{
    // Clear the window
    Window::clear();

    // Reset the maximum counter.
    mMax.reset();
}
