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
  mConfig( xpos + 2, ypos + height - 11,
           2 * width / 5, 10 ),
  mMagBar( xpos + width / 16, ypos + height / 8,
           3, 5 * height / 8 ),
  mNotes( xpos + ( width / 3 ) / 2, ypos + height / 2,
          2 * width / 3, height / 4 ),
  mTuner( xpos + ( width / 3 ) / 2, ypos + height / 16,
          2 * width / 3, 6 * height / 16 )
{
    // Draw a border around the main window
    ::box( stdscr, 0, 0 );

    // Draw title
    const char title[] = " cgt-curses " PROJECT_VERSION " ";
    mvaddstr( 0, ( width - sizeof( title ) ) / 2, title );

    // Print the box and title
    ::wnoutrefresh( stdscr );

    // Print the config ...
    mConfig.refresh();
    // ... and the rest of the windows
    end();
}

void Screen::start()
{
    // Flush harmonics.
    mHarmonics.clear();
}

void Screen::add( double freq, double mag )
{
    // Create the tone
    const util::Tone tone( freq );
    // Obtain harmonic index
    const int harm = mHarmonics.get( tone.frequency() );

    // Add magnitude to the bar
    mMagBar.add( mag );
    // Add the note to the list
    mNotes.print( tone, harm );

    // If it's a fundamental ...
    if( 0 == harm )
        // .. add to tuner
        mTuner.add( tone );
}

void Screen::end()
{
    // Print the magnitude bar
    mMagBar.refresh();
    // Print the notes
    mNotes.refresh();
    // Print the tuner
    mTuner.refresh();

    // Do the update
    ::doupdate();
}
