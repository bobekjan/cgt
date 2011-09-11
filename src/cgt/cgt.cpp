/**
 * @file cgt.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt.h"
#include "alsa/Pcm.h"

static const char         PCM_DEVICE[] = "plug:lineout_mic";
static const unsigned int PCM_CHANNELS = 2;
static const unsigned int PCM_RATE     = 48000;

int main( int argc, char* argv[] )
{
    // Prepare the PCM device
    alsa::Pcm pcm;

    alsa::Error err = pcm.open( PCM_DEVICE, SND_PCM_STREAM_PLAYBACK, 0 );
    if( err )
    {
        ::printf( "Failed to open PCM %s: %s\n", PCM_DEVICE, err.what() );
        return EXIT_FAILURE;
    }

    // Set PCM params
    err = pcm.setParams( SND_PCM_FORMAT_FLOAT64,
                         SND_PCM_ACCESS_RW_INTERLEAVED,
                         PCM_CHANNELS,
                         PCM_RATE,
                         0,
                         1200 * 1000 );
    if( err )
    {
        ::printf( "Failed to set params: %s\n", err.what() );
        return EXIT_FAILURE;
    }

    // Generate random samples
    const snd_pcm_sframes_t frames  = PCM_RATE;
    const snd_pcm_sframes_t samples = frames * PCM_CHANNELS;
    double* const           buffer  = new double[ samples ];

    for( snd_pcm_sframes_t i = 0; i < frames; ++i )
        for( snd_pcm_sframes_t j = 0; j < PCM_CHANNELS; ++j )
            buffer[ i * PCM_CHANNELS + j ] = 
                1.0 * ::sin( 2 * M_PI * 110 * i / frames ) +
                0.4 * ::sin( 2 * M_PI * 220 * i / frames ) +
                0.1 * ::sin( 2 * M_PI * 440 * i / frames );

    // Proceed with playback
    snd_pcm_sframes_t code = pcm.writeInt( buffer, frames );
    delete[] buffer;

    if( 0 > code )
    {
        ::printf( "Failed to write frames: %s\n",
                  alsa::Error( code ).what() );
        return EXIT_FAILURE;
    }
    else if( frames > code )
    {
        ::printf( "Incomplete write (requested %ld, written %ld)\n",
                  frames, code );
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
