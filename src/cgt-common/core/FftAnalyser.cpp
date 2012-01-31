/**
 * @file core/FftAnalyser.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "core/FftAnalyser.h"
#include "util/Misc.h"

using namespace cgt;
using namespace cgt::core;

/*************************************************************************/
/* cgt::core::FftAnalyser                                                */
/*************************************************************************/
FftAnalyser::FftAnalyser( IObserver& observer, double magCutoff )
: core::Analyser( observer ),
  mPlan( NULL ),
  mMagnitudeCutoff( magCutoff ),
  mFftOutput( NULL ),
  mFreqs( NULL )
{
}

void FftAnalyser::init( const char* name, unsigned int rate,
                        unsigned int bufferSize, unsigned int captureSize )
{
    // Initialize parent first.
    Analyser::init( name, rate, bufferSize, captureSize );

    // Allocate the array for frequencies.
    mFftOutput = (double*)::fftw_malloc( sizeof( double ) * this->bufferSize() );

    // We ignore DC and Nyqist frequency.
    mFreqs = new Frequency[ frequencyCount() ];

    // Setup the plan.
    mPlan = ::fftw_plan_r2r_1d( this->bufferSize(), mSamples, mFftOutput,
                                FFTW_R2HC, FFTW_MEASURE );
    // Check for error
    if( NULL == mPlan )
        throw except::RuntimeError( "Failed to prepare FFTW plan" );
}

void FftAnalyser::free()
{
    // Release the plan.
    util::safeRelease( mPlan,      ::fftw_destroy_plan );
    util::safeRelease( mFftOutput, ::fftw_free );

    util::safeDeleteArray( mFreqs );

    // Let the parent free too.
    Analyser::free();
}

void FftAnalyser::step()
{
    // Let parent process first
    Analyser::step();

    // Execute the plan
    ::fftw_execute( mPlan );

    // Process the frequencies
    processFreqs();
    processLocalMax();
    processOutput();
}

void FftAnalyser::reset()
{
    // TODO: reset all angles.
}

void FftAnalyser::processFreqs()
{
    // Ignore DC and Nyquist frequency.
    const size_t size = frequencyCount();

    // Compute magnitude for each frequency.
    for( size_t index = 0; index < size; ++index )
    {
        Frequency& freq = frequency( index );

        // Obtain FFT output.
        double real = mFftOutput[ index + 1 ];
        double img  = mFftOutput[ mBufferSize - index - 1 ];

        // Update the magnitude.
        freq.updateMagnitude( real, img );

        // Check if the magnitude is large enough.
        if( magnitudeCutoff() <= 10 * ::log10( freq.magnitude() ) )
            // Update the angle.
            freq.updateFrequency( ::atan2( img, real ) / ( 2 * M_PI )
                                  * bufferSize() / captureSize() );
        else
            // Doesn't fulfill the requirements.
            freq.reset();
    }
}

void FftAnalyser::processLocalMax()
{
    // Ignore DC and Nyquist frequency.
    const size_t size = frequencyCount();

    // Handle special case of first frequency.
    {
        Frequency& cur =  frequency( 0 );
        Frequency& next = frequency( 1 );

        if( magnitudeCutoff() <= cur.magnitude()
            && next.magnitude() < cur.magnitude() )
            cur.updateLocalMax();
    }

    // Find local maxes.
    for( size_t index = 1; index < ( size - 1 ); ++index )
    {
        Frequency& prev = frequency( index - 1 );
        Frequency& cur  = frequency( index );
        Frequency& next = frequency( index + 1 );

        if( magnitudeCutoff() <= cur.magnitude()
            && prev.magnitude() < cur.magnitude()
            && next.magnitude() < cur.magnitude() )
            cur.updateLocalMax();
    }

    // Handle special case of last frequency.
    {
        Frequency& prev = frequency( size - 2 );
        Frequency& cur  = frequency( size - 1 );

        if( magnitudeCutoff() <= cur.magnitude()
            && prev.magnitude() < cur.magnitude() )
            cur.updateLocalMax();
    }
}

void FftAnalyser::processOutput()
{
    // Ignore DC and Nyquist frequency.
    const size_t size = frequencyCount();

    // Start the observer.
    observer().start();

    // Handle special case of first frequency.
    {
        Frequency& cur =  frequency( 0 );
        Frequency& next = frequency( 1 );

        if( cur.ready() && next.localMax() < cur.localMax() )
            observer().add( ( cur.frequency() + 1 )
                            * sampleRate() / bufferSize() );
    }

    // Find local maxes.
    for( size_t index = 1; index < ( size - 1 ); ++index )
    {
        Frequency& prev = frequency( index - 1 );
        Frequency& cur  = frequency( index );
        Frequency& next = frequency( index + 1 );

        if( cur.ready()
            && prev.localMax() < cur.localMax()
            && next.localMax() < cur.localMax() )
        {
            observer().add( ( index + cur.frequency() + 1 )
                            * sampleRate() / bufferSize() );
        }
    }

    // Handle special case of last frequency.
    {
        Frequency& prev = frequency( size - 2 );
        Frequency& cur  = frequency( size - 1 );

        if( cur.ready() && prev.localMax() < cur.localMax() )
            observer().add( ( size + cur.frequency() )
                            * sampleRate() / bufferSize() );
    }

    // End observer.
    observer().end();
}

/*************************************************************************/
/* core::FftAnalyser::Frequency                                          */
/*************************************************************************/
FftAnalyser::Frequency::Frequency( unsigned int limit )
: mMagnitude( 0 ),
  mCounter( new stats::Derivative< double, double >(
                new stats::Periodic< double, double >(
                    new stats::AverageRing< double, double >( limit ),
                    1.0 ) ) ),
  mLocalMaxCount( 0 )
{
}

FftAnalyser::Frequency::~Frequency()
{
    util::safeDelete( mCounter );
}

bool FftAnalyser::Frequency::ready() const
{
    return mCounter->ready();
}

double FftAnalyser::Frequency::frequency() const
{
    return mCounter->result();
}

void FftAnalyser::Frequency::updateFrequency( double angle )
{
    mCounter->add( angle );
}

void FftAnalyser::Frequency::reset()
{
    mCounter->reset();
    mLocalMaxCount = 0;
}
