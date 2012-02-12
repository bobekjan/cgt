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
    processOutput();
}

void FftAnalyser::reset()
{
    // TODO: reset all angles.
}

double FftAnalyser::compoundMagnitude( size_t index )
{
    Frequency& cur = frequency( index );

    if( !cur.ready() )
        return cur.magnitude();

    // Ignore DC and Nyquist frequency.
    const size_t size = frequencyCount();
    // Obtain cur frequency
    double curFreq = cur.frequency();

    if( 0 == index )
    {
        if( 0 > curFreq )
            return cur.magnitude();
        else
            return ( 1 - curFreq ) * cur.magnitude()
                + curFreq * frequency( 1 ).magnitude();
    }
    else if( index == size - 1 )
    {
        if( 0 > curFreq )
            return ( 1 + curFreq ) * cur.magnitude()
                - curFreq * frequency( size - 2 ).magnitude();
        else
            return cur.magnitude();
    }
    else
    {
        if( 0 > curFreq )
            return ( 1 + curFreq ) * cur.magnitude()
                - curFreq * frequency( index - 1 ).magnitude();
        else
            return ( 1 - curFreq ) * cur.magnitude()
                + curFreq * frequency( index + 1 ).magnitude();
    }
}

bool FftAnalyser::checkFrequency( size_t indexCur, size_t indexOther )
{
    // Obtain the frequencies
    Frequency& cur   = frequency( indexCur );
    Frequency& other = frequency( indexOther );

    // Check readiness of cur
    if( !cur.ready() )
        return false;
    // Check readiness of other
    else if( !other.ready() )
        return true;
    // Compare by compound magnitudes
    else
        return compoundMagnitude( indexOther ) < compoundMagnitude( indexCur );
}

void FftAnalyser::addFrequency( size_t index )
{
    // Obtain the frequency
    Frequency& freq = frequency( index );

    // Pass it to observer
    observer().add( ( index + freq.frequency() + 1 )
                    * sampleRate() / bufferSize(),
                    freq.magnitude() );
}

void FftAnalyser::processFreqs()
{
    // Ignore DC and Nyquist frequency.
    const size_t size = frequencyCount();

    // Scale factors given by FFT.
    const double scaleMag = 1.0 / bufferSize();
    const double scaleAng = 1.0 / ( 2 * M_PI )
                            * bufferSize() / captureSize();

    // Compute magnitude for each frequency.
    for( size_t index = 0; index < size; ++index )
    {
        Frequency& freq = frequency( index );

        // Obtain FFT output.
        double real = scaleMag * mFftOutput[ index + 1 ];
        double img  = scaleMag * mFftOutput[ mBufferSize - index - 1 ];

        // Update the magnitude.
        freq.updateMagnitude( real, img );

        // Check if the magnitude is large enough.
        if( magnitudeCutoff() <= 10 * ::log10( freq.magnitude() ) )
            // Update the angle.
            freq.updateFrequency( scaleAng * ::atan2( img, real ) );
        else
            // Doesn't fulfill the requirements.
            freq.reset();
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
        if( checkFrequency( 0, 1 ) )
            addFrequency( 0 );
    }

    // Find local maxes.
    for( size_t index = 1; index < ( size - 1 ); ++index )
    {
        if( checkFrequency( index, index - 1 ) && checkFrequency( index, index + 1 ) )
            addFrequency( index );
    }

    // Handle special case of last frequency.
    {
        if( checkFrequency( size - 1, size - 2 ) )
            addFrequency( size - 1 );
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
                    1.0 ) ) )
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
}
