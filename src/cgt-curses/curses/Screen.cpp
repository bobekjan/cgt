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
Screen::Screen( int xpos, int ypos, int width, int height )
  // Pull the value from the config manager
: mHarmonics( sConfigMgr[ "cgt.fft.harmonicTolerance" ] ),
   // Carefully positioned elements
  mConfig( xpos + 1, ypos + height - 7 ),
  mNotes( xpos + ( width - 40 ) / 2, ypos + height / 2 )
{
    // Print config
    mConfig.refresh();
}

Screen::~Screen()
{
}

void Screen::start()
{
    // Flush harmonics.
    mHarmonics.clear();
    // Clear note list
    mNotes.clear();
}

void Screen::add( double freq, double )
{
    // Obtain harmonic index
    unsigned int harm = mHarmonics.get( freq );

    // Add the note to the list
    mNotes.print( freq, harm );
}

void Screen::end()
{
    // Print the notes
    mNotes.refresh();
}
