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
#include "curses/Observer.h"

int loadConfig( int argc, char* argv[] )
{
    // Load default configuration
    sConfigMgr[ "cgt.pcmDevice"   ] = "plug:hdmi_linein";
    sConfigMgr[ "cgt.pcmRate"     ] = 48000;
    sConfigMgr[ "cgt.bufferSize"  ] = 4096;
    sConfigMgr[ "cgt.captureSize" ] = 1024;

    sConfigMgr[ "cgt.fft.magnitudeCutoff" ] = 7.5;

    // Load config
    config::ArgvParser argvParser;
    argvParser.addConfig();
    argvParser.addHelp();

    // Define value options
    argvParser.addValue( 'D', "device", "cgt.pcmDevice",
                         "Name of ALSA device to use" );
    argvParser.addValue( 'r', "rate", "cgt.pcmRate",
                         "Sample rate to use" );
    argvParser.addValue( 'B', "buffer-size", "cgt.bufferSize",
                         "Buffer size to use" );
    argvParser.addValue( 'C', "capture-size", "cgt.captureSize",
                         "Capture size to use" );
    argvParser.addValue( 'm', "mag-cutoff", "cgt.fft.magnitudeCutoff",
                         "Magnitude cutoff value when using FFT" );

    // Parse arg vector
    return argvParser.parse( argc, argv );
}

int main( int argc, char* argv[] )
{
    // Setup configuration
    int code = loadConfig( argc, argv );
    if( 0 > code )
        return EXIT_FAILURE;

    // Shift arg vector
    argc -= code;
    argv += code;

    // Init curses screen
    curses::LibInit curs;
    curs.cBreak();
    curs.noEcho();
    curs.setCursor( 0 );
    curs.setTimeout( 0 );

    // Allocate the necessary classes
    curses::Observer  obs;
    core::FftAnalyser analyser( obs, sConfigMgr[ "cgt.fft.magnitudeCutoff" ] );

    // Initialize the process
    if( !analyser.init( sConfigMgr[ "cgt.pcmDevice" ],
                        sConfigMgr[ "cgt.pcmRate" ],
                        sConfigMgr[ "cgt.bufferSize" ],
                        sConfigMgr[ "cgt.captureSize" ] ) )
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

    return EXIT_SUCCESS;
}
