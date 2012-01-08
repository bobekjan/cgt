/**
 * @file cgt-curses.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/Observer.h"

void loadDefaultCfg()
{
    sConfigMgr[ "cgt-curses.pcmDevice"   ] = "plug:hdmi_linein";
    sConfigMgr[ "cgt-curses.pcmRate"     ] = 48000;
    sConfigMgr[ "cgt-curses.bufferSize"  ] = 1024;
    sConfigMgr[ "cgt-curses.captureSize" ] = 1024;

    sConfigMgr[ "cgt-curses.fft.magnitudeCutoff" ] = 0.5;
}

int main( void )
{
    // Setup configuration
    loadDefaultCfg();

    // Init curses screen
    ::initscr();
    ::curs_set( 0 );
    ::cbreak();
    ::noecho();
    ::timeout( 0 );

    // Allocate the necessary classes
    curses::Observer  obs;
    core::FftAnalyser analyser( obs, sConfigMgr[ "cgt-curses.fft.magnitudeCutoff" ] );

    // Initialize the process
    if( !analyser.init( sConfigMgr[ "cgt-curses.pcmDevice" ],
                        sConfigMgr[ "cgt-curses.pcmRate" ],
                        sConfigMgr[ "cgt-curses.bufferSize" ],
                        sConfigMgr[ "cgt-curses.captureSize" ] ) )
    {
        ::puts( "Failed to initialize PCM" );
        return EXIT_FAILURE;
    }

    // Main loop
    while( 'q' != ::getch() )
    {
        // Run the step
        if( !analyser.step() )
        {
            ::puts( "An error occurred during processing" );
            return EXIT_FAILURE;
        }
    }

    // End curses mode
    ::endwin();

    return EXIT_SUCCESS;
}
