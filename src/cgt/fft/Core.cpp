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
  mCapture( &Core::captureFull ),
  mBufferSize( 0 ),
  mCaptureSize( 0 ),
  mSamples( NULL ),
  mFreqs( NULL ),
  mMags( NULL ),
  mPlan( NULL )
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
                         1, rate, 0, 1000 * 40 ) )
        return false;

    // Setup the buffers.
    mBufferSize  = bufferSize;
    mCaptureSize = captureSize;
    mSamples     = (double*)::fftw_malloc( sizeof( double ) * mBufferSize );
    mFreqs       = (double*)::fftw_malloc( sizeof( double ) * mBufferSize );

    mMags        = new double[ mBufferSize / 2 + 1 ];

    // Setup the plan.
    ::printf( "Building the FFTW plan\n" );

    mPlan = ::fftw_plan_r2r_1d( mBufferSize, mSamples, mFreqs,
                                FFTW_R2HC, FFTW_MEASURE );
    if( NULL == mPlan )
    {
        ::printf( "Failed to build FFTW plan\n" );
        return false;
    }

    ::printf( "FFTW plan built\n" );

    return true;
}

void Core::freePcm()
{
    // Release the plan and buffers.
    util::safeRelease( mPlan, ::fftw_destroy_plan );

    mBufferSize  = 0;
    mCaptureSize = 0;
    util::safeRelease( mSamples, ::fftw_free );
    util::safeRelease( mFreqs,   ::fftw_free );

    util::safeDeleteArray( mMags );

    // Reset the state to default
    mCapture = &Core::captureFull;

    // Free the PCM.
    util::safeDelete( mPcm );
}

bool Core::step()
{
    // Do the capture
    if( !( this->*mCapture )() )
        return false;
    // Execute FFTW plan
    else if( !executePlan() )
        return false;
    // Compute magnitudes
    else if( !computeMags() )
        return false;

    ::printf( "0:[%6.3lf] 1:[%6.3lf] 2:[%6.3lf]\n",
              mMags[ 0 ], mMags[ 1 ], mMags[ 2 ] );

    return true;
}

bool Core::reset()
{
    // Refill the buffer entirely
    mCapture = &Core::captureFull;

    return true;
}

bool Core::captureFull()
{
    // Fill the buffer entirely.
    void* buf[] = { &mSamples[ 0 ] };
    snd_pcm_sframes_t code = mPcm->readNonint( buf, mBufferSize );

    // Has an error occurred?
    if( 0 > code )
        return false;
    // Have we read too little?
    else if( mBufferSize > code )
        return false;

    // Next time, run only a step capture
    mCapture = &Core::captureStep;

    return true;
}

bool Core::captureStep()
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

bool Core::executePlan()
{
    // Execute the plan
    ::fftw_execute( mPlan );

    return true;
}

bool Core::computeMags()
{
    // DC has no imaginary part
    mMags[ 0 ] = ::fabs( mFreqs[ 0 ] );

    // Compute the rest
    const size_t size = ( mBufferSize - 1 ) / 2 + 1;
    for( size_t i = 1; i < size; ++i )
    {
        const double real = mFreqs[ i ];
        const double img  = mFreqs[ mBufferSize - i ];

        // Compute magnitude
        mMags[ i ] = ::sqrt( real * real + img * img );
    }

    // If buffer size is even, we have one more freq to handle.
    if( 0 == mBufferSize % 2 )
        mMags[ size ] = mFreqs[ size ];

    return true;
}
