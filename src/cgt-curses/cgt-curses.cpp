/**
 * @file cgt-curses.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "curses/LibInit.h"
#include "curses/Screen.h"

int main( int argc, char* argv[] )
{
    try
    {
        // Load default configuration
        sConfigMgr[ "cgt.pcm.device"  ] = "hw:0,0";
        sConfigMgr[ "cgt.pcm.rate"    ] = 48000;
        sConfigMgr[ "cgt.bufferSize"  ] = 8192;
        sConfigMgr[ "cgt.captureSize" ] = 2048;

        sConfigMgr[ "cgt.fft.magnitudeCutoff" ]   = 10.0;
        sConfigMgr[ "cgt.fft.harmonicTolerance" ] = -6.0;

        // Load config
        config::ArgvParser argvParser;
        argvParser.addConfig();
        argvParser.addHelp();

        // Define value options
        argvParser.addValue( 'D', "device", "cgt.pcm.device",
                             "Name of ALSA device to use" );
        argvParser.addValue( 'r', "rate", "cgt.pcm.rate",
                             "Sample rate to use" );
        argvParser.addValue( 'B', "buffer-size", "cgt.bufferSize",
                             "Buffer size to use" );
        argvParser.addValue( 'C', "capture-size", "cgt.captureSize",
                             "Capture size to use" );
        argvParser.addValue( 'm', "mag-cutoff", "cgt.fft.magnitudeCutoff",
                             "Magnitude cutoff value when using FFT" );
        argvParser.addValue( 'H', "harm-tol", "cgt.fft.harmonicTolerance",
                             "Harmonic tolerance value" );

        // Parse arg vector
        int code = argvParser.parse( argc, argv );
        argc -= code;
        argv += code;
    }
    catch( const std::exception& e )
    {
        // Print an error message
        ::fprintf( stderr, "Failed to setup configuration: %s\n", e.what() );
        return EXIT_FAILURE;
    }

    try
    {
        // Init curses screen
        curses::LibInit curs;
        curs.cBreak();
        curs.noEcho();
        curs.startColor();
        curs.useDefaultColors();
        curs.setCursor( 0 );
        curs.setTimeout( 0 );

        // Obtain screen parameters
        int width, height;
        getmaxyx( stdscr, height, width );

        // Allocate the necessary classes
        curses::Screen scr( 0, 0, width, height );
        core::FftAnalyser analyser( scr, sConfigMgr[ "cgt.fft.magnitudeCutoff" ] );

        // Initialize the process
        analyser.init( sConfigMgr[ "cgt.pcm.device" ],
                       sConfigMgr[ "cgt.pcm.rate" ],
                       sConfigMgr[ "cgt.bufferSize" ],
                       sConfigMgr[ "cgt.captureSize" ] );

        // Main loop
        while( 'q' != ::getch() )
            // Run the step
            analyser.step();
    }
    catch( const std::exception& e )
    {
        // Print an error message
        ::fprintf( stderr, "Fatal error: %s\n", e.what() );
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
