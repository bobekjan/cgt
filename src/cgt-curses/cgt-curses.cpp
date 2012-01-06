/**
 * @file cgt-curses.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-curses.h"

#include "alsa/Pcm.h"
#include "config/ConfigMgr.h"
#include "core/FftAnalyser.h"
#include "util/Misc.h"

class DebugObserver
: public core::Analyser::IObserver
{
public:
#ifdef CGT_DEBUG_ANALYSE_HARMONICS
    unsigned int getHarmonic( double freq )
    {
        std::vector< double >::const_iterator cur, end;
        cur = mFundamentals.begin();
        end = mFundamentals.end();
        for(; cur != end; ++cur )
        {
            // Calculate ratio of the frequencies.
            double ratio = freq / *cur;
            // Round it to the nearest integer.
            int k = ratio + 0.5;

            // If the error is small enough, return the ratio.
            if( -9.0 > 10 * ::log10( ::fabs( ratio - k ) ) )
                return k - 1;
        }

        // Add a new fundamental.
        mFundamentals.push_back( freq );
        return 0;
    }
    void clearHarmonic()
    {
        mFundamentals.clear();
    }
#endif /* CGT_DEBUG_ANALYSE_HARMONICS */

    void add( double freq )
    {
        // Generate the name
        util::nameFreq( freq, mName, sizeof( mName ) );

        // Obtain harmonic index
        unsigned int harm = getHarmonic( freq );

        // Print it
#ifndef CGT_DEBUG_ANALYSIS_FREQ
        ::printf( "[%-*u] %10s (%10.4f Hz)\n",
                  (int)::log2( harm + 1 ) + 1, harm, mName, freq );
#else /* !CGT_DEBUG_ANALYSIS_FREQ */
        ::printf( "[%-*u] %10s (%10.4f Hz) = %10.4f dB\n",
                  (int)::log2( harm + 1 ) + 1, harm, mName, freq,
                  10 * ::log10( ::fabs( freq - CGT_DEBUG_ANALYSIS_FREQ ) ) );
#endif /* !CGT_DEBUG_ANALYSIS_FREQ */
    }
    void clear()
    {
        // Print a line as a separator.
        ::puts( "----------" );

        // Flush harmonics.
        clearHarmonic();
    }

protected:
#ifdef CGT_DEBUG_ANALYSE_HARMONICS
    /// A vector of fundamentals.
    std::vector< double > mFundamentals;
#endif /* CGT_DEBUG_ANALYSE_HARMONICS */

    /// A buffer for note name.
    char mName[ 0x20 ];
};


int main( void )
{
    // Setup configuration
    sConfigMgr[ "cgt-curses.pcmDevice"   ] = "plug:hdmi_linein";
    sConfigMgr[ "cgt-curses.pcmRate"     ] = 48000;
    sConfigMgr[ "cgt-curses.bufferSize"  ] = 1024;
    sConfigMgr[ "cgt-curses.captureSize" ] = 1024;

    sConfigMgr[ "cgt-curses.fft.magnitudeCutoff" ] = 0.5;

    // Allocate the necessary classes.
    // ui::Curses obs;
    DebugObserver obs;
    core::FftAnalyser analyser( obs, sConfigMgr[ "cgt-curses.fft.magnitudeCutoff" ] );

    // Initialize the process.
    if( !analyser.init( sConfigMgr[ "cgt-curses.pcmDevice" ],
                        sConfigMgr[ "cgt-curses.pcmRate" ],
                        sConfigMgr[ "cgt-curses.bufferSize" ],
                        sConfigMgr[ "cgt-curses.captureSize" ] ) )
    {
        ::printf( "Failed to initialize PCM\n" );
        return EXIT_FAILURE;
    }

    while( true )
    {
        // Run the step.
        if( !analyser.step() )
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
