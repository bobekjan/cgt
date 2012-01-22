/**
 * @file curses/Screen.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/Screen.h"

using namespace cgt::curses;

/*************************************************************************/
/* cgt::curses::Screen                                                   */
/*************************************************************************/
Screen::Screen( int row, int col, int width, int height )
: mWidth( 0 ),
  mHeight( 0 ),
  // Pull the value from the config manager
  mHarmonics( sConfigMgr[ "cgt.fft.harmonicTolerance" ] ),
  // Carefully positioned elements
  mConfig( height - 7, col + 1 ),
  mNotes( row + height / 2, col + ( width - 40 ) / 2 )
{
}

Screen::~Screen()
{
}

void Screen::start()
{
    // Wipe the screen
    ::clear();

    // Flush harmonics.
    mHarmonics.clear();

    // Print config
    mConfig.print();
    // Clear note list
    mNotes.clear();
}

void Screen::add( double freq )
{
    // Obtain harmonic index
    unsigned int harm = mHarmonics.get( freq );

    // Add the note to the list
    mNotes.add( freq, harm );
}

void Screen::end()
{
    // Print the buffer
    ::refresh();
}
