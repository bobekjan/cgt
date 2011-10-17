/**
 * @file fft/Core.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt.h"
#include "fft/Core.h"

using namespace fft;

/*************************************************************************/
/* fft::Core                                                             */
/*************************************************************************/
Core::Core( IObserver& observer )
: mObserver( &observer ),
  mPcm( NULL ),
  mBufferSize( 0 ),
  mCaptureSize( 0 ),
  mSamples( NULL )
{
}

Core::~Core()
{
    // Free the PCM.
    freePcm();
}

bool Core::initPcm( const char* name, unsigned int rate,
                    unsigned int bufferSize, unsigned int captureSize )
{
    // Make sure the sizes are valid.
    if( bufferSize < captureSize )
        return false;

    // Make sure the PCM is not initialized.
    freePcm();
    mPcm = new alsa::Pcm( name, SND_PCM_STREAM_CAPTURE, 0 );

    // We want doubles of one channel at the given rate.
    if( mPcm->setParams( SND_PCM_FORMAT_FLOAT64,
                         SND_PCM_ACCESS_RW_NONINTERLEAVED,
                         1, rate, 0, 0 ) )
        return false;

    // Setup the buffers.
    mBufferSize  = bufferSize;
    mCaptureSize = captureSize;
    mSamples     = new double[ mBufferSize ];

    return true;
}

void Core::freePcm()
{
    // Release the buffers.
    delete[] mSamples;
    mSamples = NULL;

    mBufferSize  = 0;
    mCaptureSize = 0;

    // Free the PCM.
    if( NULL != mPcm )
        delete mPcm;

    mPcm = NULL;
}

bool Core::stepFirst()
{
    // When running for the first time, fill the buffer entirely.
    void* buf[] = { &mSamples[ 0 ] };
    snd_pcm_sframes_t code = mPcm->readNonint( buf, mBufferSize );

    // Has an error occurred?
    if( 0 > code )
        return false;
    // Have we read too little?
    else if( mBufferSize > code )
        return false;

    return true;
}

bool Core::stepNext()
{
    // We want to get only the capture size, shift the buffer first.
    ::memmove( &mSamples[ 0 ], &mSamples[ mCaptureSize ],
               mBufferSize - mCaptureSize );

    // Capture only the capture size.
    void* buf[] = { &mSamples[ mBufferSize - mCaptureSize ] };
    snd_pcm_sframes_t code = mPcm->readNonint( buf, mCaptureSize );

    // Has an error occurred?
    if( 0 > code )
        return false;
    // Have we read too little?
    else if( mCaptureSize > code )
        return false;

    return true;
}
