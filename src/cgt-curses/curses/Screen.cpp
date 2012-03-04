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
  mConfig( xpos, ypos + height - 9,
           width / 2, 9 ),
  mMagBar( xpos + width / 16, ypos + height / 8,
           3, 5 * height / 8 ),
  mNotes( xpos + ( width / 3 ) / 2, ypos + height / 2,
          2 * width / 3, height / 4 ),
  mTuner( xpos + ( width / 3 ) / 2, ypos + height / 16,
          2 * width / 3, 6 * height / 16 )
{
    // Initial print of all windows
    mConfig.refresh();
    mMagBar.refresh();
    mNotes.refresh();
    mTuner.refresh();
}

void Screen::start()
{
    // Flush harmonics.
    mHarmonics.clear();

    // Clear magnitude bar.
    mMagBar.clear();
    // Clear note list
    mNotes.clear();
    // Clear tuner
    mTuner.clear();
}

void Screen::add( double freq, double mag )
{
    // Obtain harmonic index
    const int harm = mHarmonics.get( freq );

    // Add magnitude to the bar
    mMagBar.add( mag );
    // Add the note to the list
    mNotes.print( freq, harm );

    // If it's a fundamental ...
    if( 0 == harm )
        // .. add to tuner
        mTuner.add( freq );
}

void Screen::end()
{
    // Print the magnitude bar
    mMagBar.refresh();
    // Print the notes
    mNotes.refresh();
    // Print the tuner
    mTuner.refresh();
}
