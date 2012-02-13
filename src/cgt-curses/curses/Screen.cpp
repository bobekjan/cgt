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
  mConfig( xpos, ypos + height - 8,
           width / 3, 8 ),
  mMagBar( xpos + width / 16, ypos + height / 8,
           3, 5 * height / 8 ),
  mNotes( xpos + ( width / 3 ) / 2, ypos + height / 2,
          2 * width / 3, height / 4 )
{
    // Initial print of all windows
    mConfig.refresh();
    mMagBar.refresh();
    mNotes.refresh();
}

Screen::~Screen()
{
}

void Screen::start()
{
    // Flush harmonics.
    mHarmonics.clear();
    // Clear magnitude bar.
    mMagBar.clear();
    // Clear note list
    mNotes.clear();
}

void Screen::add( double freq, double mag )
{
    // Add magnitude to the bar
    mMagBar.add( mag );
    // Add the note to the list
    mNotes.print( freq, mHarmonics.get( freq ) );
}

void Screen::end()
{
    // Print the magnitude bar
    mMagBar.refresh();
    // Print the notes
    mNotes.refresh();
}
