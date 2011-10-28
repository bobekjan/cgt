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
#include "util/Misc.h"

using namespace fft;

/*************************************************************************/
/* fft::Core                                                             */
/*************************************************************************/
bool ( Core::* Core::CAPTURE_ROUTINES[] )() =
{
    &Core::captureFull, // CAPTURE_FULL
    &Core::captureStep  // CAPTURE_STEP
};

Core::Core( IObserver& observer, double ampCutoff, double bindCutoff )
: mObserver( &observer ),
  mPcm( NULL ),
  mPlan( NULL ),
  mCapture( CAPTURE_FULL ),
  mSampleRate( 0 ),
  mBufferSize( 0 ),
  mCaptureSize( 0 ),
  mAmplitudeCutoff( ampCutoff ),
  mBindCutoff( bindCutoff ),
  mSamples( NULL ),
  mFreqs( NULL ),
  mMags( NULL ),
  mAngles( NULL )
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

    // Create the PCM object.
    mPcm = new alsa::Pcm( name, SND_PCM_STREAM_CAPTURE, 0 );

    // We want doubles of one channel at the given rate.
    if( mPcm->setParams( SND_PCM_FORMAT_FLOAT64,
                         SND_PCM_ACCESS_RW_NONINTERLEAVED,
                         1, rate, 0, 100 * 1000 ) )
        return false;

    // Setup the buffers.
    mSampleRate  = rate;
    mBufferSize  = bufferSize;
    mCaptureSize = captureSize;

    mSamples = (double*)::fftw_malloc( sizeof( double ) * mBufferSize );
    mFreqs   = (double*)::fftw_malloc( sizeof( double ) * mBufferSize );

    // We ignore DC and Nyqist frequency.
    const size_t size = ( mBufferSize - 1 ) / 2;

    mMags   = new double[ size ];
    mAngles = new Angle[ size ];

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
    // Release the plan.
    util::safeRelease( mPlan, ::fftw_destroy_plan );

    // Release the buffers.
    mSampleRate  = 0;
    mBufferSize  = 0;
    mCaptureSize = 0;

    util::safeRelease( mSamples, ::fftw_free );
    util::safeRelease( mFreqs,   ::fftw_free );

    util::safeDeleteArray( mMags );
    util::safeDeleteArray( mAngles );

    // Reset the state to default
    mCapture = CAPTURE_FULL;

    // Free the PCM.
    util::safeDelete( mPcm );
}

bool Core::step()
{
    // Do the capture
    if( !( this->* ( CAPTURE_ROUTINES[ mCapture ] ) )() )
        return false;

    // Execute FFTW plan
    if( !executePlan() )
        return false;

    // Process the frequencies
    if( !processFreqs() )
        return false;

    // // Notify the observer of new analysis.
    // observer().clear();

    // // Ignore DC and Nyquist frequency
    // const size_t size = ( mBufferSize - 1 ) / 2 + 1;

    // for( size_t i = 1; i < size; ++i )
    //     if( !handleFrequency( i ) )
    //         return false;

    return true;
}

bool Core::reset()
{
    // Refill the buffer entirely
    mCapture = CAPTURE_FULL;

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
    mCapture = CAPTURE_STEP;

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

bool Core::processFreqs()
{
    observer().clear();

    // Ignore DC and Nyquist frequency.
    const size_t size = ( mBufferSize - 1 ) / 2;

    // Compute magnitude for each frequency.
    for( size_t i = 0; i < size; ++i )
    {
        const double real = mFreqs[ i + 1 ];
        const double img  = mFreqs[ mBufferSize - ( i + 1 ) ];

        mMags[ i ] = ::sqrt( real * real + img * img );

        // -------------------------------------------
        const double freq =
            (double)( i + 1 )
            * (double)mSampleRate
            / (double)mBufferSize;

        Angle& ang = mAngles[ i ];

        if( amplitudeCutoff() <= mMags[ i ] )
        {
            ang.update( ::atan2( img, real ) );

            observer().add( freq + ang.frequency() );
        }
        else
        {
            ang.reset();
        }
    }

    // // Is the first one suitable?
    // if( amplitudeCutoff() <= mMags[ 0 ]
    //     && mMags[ 1 ] < mMags[ 0 ] )
    // {
    //     // Is the neighbour large enough?
    //     if( bindCutoff() <= 10 * ::log10( mMags[ 1 ] / mMags[ 0 ] ) )
    //     {
    //         if( !processBoundFreq( 0, 1 ) )
    //             return false;
    //     }
    //     else
    //     {
    //         if( !processSingleFreq( 0 ) )
    //             return false;
    //     }
    // }

    // for( size_t i = 1; i < ( size - 1 ); ++i )
    // {
    //     // Is the i-th one suitable?
    //     if( amplitudeCutoff() <= mMags[ i ]
    //         && mMags[ i - 1 ] < mMags[ i ]
    //         && mMags[ i + 1 ] < mMags[ i ] )
    //     {
    //         // Which of the neighbours is larger?
    //         const size_t boundIndex =
    //             mMags[ i - 1 ] < mMags[ i + 1 ]
    //             ? i + 1
    //             : i - 1;

    //         // Is the neighbour large enough?
    //         if( bindCutoff() <= 10 * ::log10( mMags[ boundIndex ] / mMags[ i ] ) )
    //         {
    //             if( !processBoundFreq( i, boundIndex ) )
    //                 return false;
    //         }
    //         else
    //         {
    //             if( !processSingleFreq( i ) )
    //                 return false;
    //         }
    //     }
    // }

    // // Is the last one suitable?
    // if( amplitudeCutoff() <= mMags[ size - 1 ]
    //     && mMags[ size - 2 ] < mMags[ size - 1 ] )
    // {
    //     // Is the neighbour large enough?
    //     if( bindCutoff() <= 10 * ::log10( mMags[ size - 2 ] / mMags[ size - 1 ] ) )
    //     {
    //         if( !processBoundFreq( size - 1, size - 2 ) )
    //             return false;
    //     }
    //     else
    //     {
    //         if( !processSingleFreq( size - 1 ) )
    //             return false;
    //     }
    // }

    return true;
}

bool Core::processSingleFreq( size_t index )
{
    // const double freq =
    //     (double)( index + 1 )
    //     * (double)mSampleRate
    //     / (double)mBufferSize;

    // Angle& ang = mAngles[ index ];

    return true;
}

bool Core::processBoundFreq( size_t index, size_t boundIndex )
{
    const double freq = (double)index * (double)mSampleRate / (double)mBufferSize;

    const double cur  = mMags[ index ];
    const double prev = mMags[ index - 1 ];
    const double next = mMags[ index + 1 ];

    Angle& ang = mAngles[ index ];

    // Check if the amplitude is big enough and a local max
    if( amplitudeCutoff() < cur
        && prev < cur && cur > next )
    {
        // Compute current angle.
        const double angle = ::atan2( mFreqs[ mBufferSize - index ],
                                      mFreqs[ index ] );

        // Update the angle information.
        ang.update( angle );

        // Determine which neighbor in bigger in magnitude.
        size_t boundIndex = index - 1;
        double boundValue = prev;

        if( boundValue < next )
        {
            boundIndex = index + 1;
            boundValue = next;
        }

        // Determine if the frequencies are bound.
        if( bindCutoff() <= 10 * ::log10( boundValue / cur ) )
        {
            // Compute current bound angle.
            const double boundAngle = ::atan2( mFreqs[ mBufferSize - boundIndex ],
                                               mFreqs[ boundIndex ] );

            // Update the bound angle information.
            mAngles[ boundIndex ].update( boundAngle );
        }
        else
        {
            // Notify observer of the frequency.
            observer().add( freq + ang.frequency() );
        }
    }
    else
    {
        // The frequency is not present, reset.
        ang.reset();
    }

    return true;
}

/*************************************************************************/
/* fft::Core::Angle                                                      */
/*************************************************************************/
Core::Angle::Angle()
: mAngle( 0.0 ),
  mAvSum( 0.0 ),
  mSamples( 0 )
{
}

double Core::Angle::frequency() const
{
    return mAvSum / ( 2.0 * M_PI * mSamples );
}

void Core::Angle::update( double angle )
{
    // Compute angular velocity and normalize it
    const double av = util::normalizeAngle( angle - mAngle, 2.0 * M_PI );

    // Update the angle and angular velocity sum
    mAngle  = angle;
    mAvSum += av;

    // Increment number of samples.
    ++mSamples;
}

void Core::Angle::reset()
{
    // Just zero all members.
    mAngle   = 0.0;
    mAvSum   = 0.0;
    mSamples = 0;
}
