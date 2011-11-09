/**
 * @file cgt.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-cli.h"

#include "alsa/Pcm.h"
#include "fft/Core.h"
#include "util/Misc.h"

const char         PCM_DEVICE[] = "plug:hdmi_linein";
const unsigned int PCM_RATE     = 48000;
// const unsigned int PCM_CHANNELS = 1;
// const unsigned int PCM_LATENCY  = 100 * 1000; /* 100 ms */

const unsigned int BUFFER_SIZE      = 4096;
const unsigned int CAPTURE_SIZE     = 1024;
const double       AMPLITUDE_CUTOFF = 2.0;
const double       BIND_CUTOFF      = -2.0;

class DebugObserver
: public fft::Core::IObserver
{
public:
    void add( double freq )
    {
        // Generate the name
        util::nameFreq( freq, mName, sizeof( mName ) );

        // Print it
        ::printf( "%10s [%10.4f Hz]\n", mName, freq );
    }
    void clear()
    {
        // Print a line as a separator.
        ::puts( "----------" );
    }

protected:
    char mName[ 0x20 ];
};


int main( int argc, char* argv[] )
{
    // Allocate the necessary classes.
    // ui::Curses obs;
    DebugObserver obs;
    fft::Core     core( obs, AMPLITUDE_CUTOFF, BIND_CUTOFF );

    // Initialize the process.
    if( !core.initPcm( "plug:hdmi_linein", PCM_RATE, BUFFER_SIZE, CAPTURE_SIZE ) )
    {
        ::printf( "Failed to initialize PCM\n" );
        return EXIT_FAILURE;
    }

    while( true )
    {
        // Run the step.
        if( !core.step() )
        {
            ::printf( "An error occurred during processing\n" );
            return EXIT_FAILURE;
        }
    }

    // // Prepare the PCM device
    // alsa::Pcm pcm;

    // alsa::Error err = pcm.open( PCM_DEVICE, SND_PCM_STREAM_CAPTURE, 0 );
    // if( err )
    // {
    //     ::printf( "Failed to open PCM %s: %s\n", PCM_DEVICE, err.what() );
    //     return EXIT_FAILURE;
    // }

    // // Set PCM params
    // err = pcm.setParams( SND_PCM_FORMAT_FLOAT64,
    //                      SND_PCM_ACCESS_RW_NONINTERLEAVED,
    //                      PCM_CHANNELS, PCM_RATE, 0, PCM_LATENCY );
    // if( err )
    // {
    //     ::printf( "Failed to set params: %s\n", err.what() );
    //     return EXIT_FAILURE;
    // }

    // // Prepare stuff
    // double sampleSum = 0.0;
    // unsigned long sampleCount = 0;

    // double* buffer = new double[ BUFFER_SIZE ];

    // while( true )
    // {
    //     // Capture some samples
    //     snd_pcm_sframes_t code = pcm.readNonint( reinterpret_cast< void** >( &buffer ),
    //                                              BUFFER_SIZE );

    //     // Check for errors
    //     if( 0 > code )
    //     {
    //         err = code;

    //         ::printf( "Failed to read frames: %s\n", err.what() );
    //         return EXIT_FAILURE;
    //     }
    //     else if( BUFFER_SIZE > code )
    //     {
    //         ::printf( "Incomplete read (requested %u, read %ld)\n",
    //                   BUFFER_SIZE, code );
    //         return EXIT_FAILURE;
    //     }

    //     // Sum all samples
    //     for( unsigned int i = 0; i < BUFFER_SIZE; ++i )
    //         sampleSum += buffer[ i ];

    //     sampleCount += BUFFER_SIZE;

    //     // Print running sum
    //     ::fprintf( stdout, "\rsum: [%13.4f] samples: [%10lu] avg [%13.4g]",
    //                sampleSum, sampleCount, sampleSum / sampleCount );
    //     ::fflush( stdout );
    // }

    // // Release the buffer
    // delete[] buffer;
    // buffer = NULL;

    return EXIT_SUCCESS;
}
