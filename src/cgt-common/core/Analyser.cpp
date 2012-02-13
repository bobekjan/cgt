/**
 * @file core/Analyser.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "core/Analyser.h"

using namespace cgt;
using namespace cgt::core;

/*************************************************************************/
/* cgt::core::Analyser                                                   */
/*************************************************************************/
void ( Analyser::* Analyser::CAPTURE_ROUTINES[] )() =
{
    &Analyser::captureFull, // CAPTURE_FULL
    &Analyser::captureStep  // CAPTURE_STEP
};

Analyser::Analyser( IObserver& observer )
: mObserver( &observer ),
  mPcm( NULL ),
#ifdef CGT_DEBUG_ANALYSIS_FREQ
  mPhase( 0 ),
#endif /* CGT_DEBUG_ANALYSIS_FREQ */
  mCapture( CAPTURE_FULL ),
  mSampleRate( 0 ),
  mBufferSize( 0 ),
  mCaptureSize( 0 ),
  mSamples( NULL )
{
}

Analyser::~Analyser()
{
    // Free all resources.
    free();
}

void Analyser::init( const char* name, unsigned int rate,
                     unsigned int bufferSize, unsigned int captureSize )
{
    // Make sure the sizes are valid.
    if( bufferSize < captureSize )
        throw except::InvalidArgument(
            ::ssprintf( "Capture size (%u) larger than buffer size (%u)",
                        captureSize, bufferSize ) );

    // Make sure all resources are freed first.
    free();

    // Create the PCM object.
    mPcm = new alsa::Pcm( name, SND_PCM_STREAM_CAPTURE, 0 );

    // We want doubles of one channel at the given rate.
    mPcm->setParams( SND_PCM_FORMAT_FLOAT64,
                     SND_PCM_ACCESS_RW_NONINTERLEAVED,
                     1, rate, 0, -1 );

    // Setup the buffers.
    mSampleRate  = rate;
    mBufferSize  = bufferSize;
    mCaptureSize = captureSize;

    mSamples = new double[ this->bufferSize() ];
}

void Analyser::free()
{
    // Release the buffers.
    util::safeDeleteArray( mSamples );

    mSampleRate  = 0;
    mBufferSize  = 0;
    mCaptureSize = 0;

#ifdef CGT_DEBUG_ANALYSIS_FREQ
    mPhase = 0;
#endif /* CGT_DEBUG_ANALYSIS_FREQ */

    // Reset the state to default
    mCapture = CAPTURE_FULL;

    // Free the PCM.
    util::safeDelete( mPcm );
}

void Analyser::reset()
{
    // Refill the buffer entirely
    mCapture = CAPTURE_FULL;
}

void Analyser::captureFull()
{
#ifndef CGT_DEBUG_ANALYSIS_FREQ
    // Fill the buffer entirely.
    void* buf[] = { &mSamples[ 0 ] };
    snd_pcm_sframes_t code = mPcm->readNonint( buf, bufferSize() );

    // Have we read too little?
    if( code < bufferSize() )
        // Throw an error message
        throw except::UnderflowError(
            ::ssprintf( "Read only %ld non-interleaved samples (expected %u)",
                        code, bufferSize() ) );
#else /* CGT_DEBUG_ANALYSIS_FREQ */
    for( size_t i = 0;
         i < bufferSize();
         ++i, mPhase += 2.0 * M_PI / sampleRate() )
        mSamples[ i ] = ::cos( CGT_DEBUG_ANALYSIS_FREQ * mPhase );
#endif /* CGT_DEBUG_ANALYSIS_FREQ */

    // Next time, run only a step capture
    mCapture = CAPTURE_STEP;
}

void Analyser::captureStep()
{
    // We want to get only the capture size, shift the buffer first.
    ::memmove( &mSamples[ 0 ], &mSamples[ captureSize() ],
               sizeof( double ) * ( bufferSize() - captureSize() ) );

#ifndef CGT_DEBUG_ANALYSIS_FREQ
    // Capture only the capture size.
    void* buf[] = { &mSamples[ bufferSize() - captureSize() ] };
    snd_pcm_sframes_t code = mPcm->readNonint( buf, captureSize() );

    // Have we read too little?
    if( code < captureSize() )
        // Throw an error message
        throw except::UnderflowError(
            ::ssprintf( "Read only %ld non-interleaved samples (expected %u)",
                        code, captureSize() ) );
#else /* CGT_DEBUG_ANALYSIS_FREQ */
    for( size_t i = bufferSize() - captureSize();
         i < bufferSize();
         ++i, mPhase += 2.0 * M_PI / sampleRate() )
        mSamples[ i ] = ::cos( CGT_DEBUG_ANALYSIS_FREQ * mPhase );

    ::usleep( 1000lu * 1000lu * captureSize() / sampleRate() );
#endif /* CGT_DEBUG_ANALYSIS_FREQ */
}
