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
  mCutoff( sConfigMgr[ "cgt.fft.magnitudeCutoff" ] ),
  mSpan( sConfigMgr[ "cgt.tune.magSpan" ] )
{
    // Init our colors
    ::init_pair( PAIR_MAGBAR, COLOR_WHITE, -1 );

    // Draw a box
    box();
}

void MagnitudeBar::add( double mag )
{
    // Pass it to maximum.
    mMax.add( mag );
}

void MagnitudeBar::refresh()
{
    // Obtain dimensions of the window
    int width, height;
    getmaxyx( mWindow, height, width );

    // Check if the counter is ready
    if( mMax.ready() )
    {
        // Obtain the maximum
        double mag = 10 * ::log10( mMax.result() );

        // Calculate bar
        int bar = ( height - 2 ) * std::min( ( mag - mCutoff ) / mSpan, 1.0 );

        // Print the colorized bar
        attrOn( COLOR_PAIR( PAIR_MAGBAR ) );
        mvwvline( mWindow, height - bar - 1, 1, '*', bar );
        attrOff( COLOR_PAIR( PAIR_MAGBAR ) );
    }

    // Refresh content of the window
    Window::noutRefresh();

    // Reset bar level
    mvwvline( mWindow, 1, 1, ' ', height - 2 );
    // Reset the maximum counter.
    mMax.reset();
}
