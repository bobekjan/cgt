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

using namespace core;

/*************************************************************************/
/* core::FftAnalyser                                                     */
/*************************************************************************/
FftAnalyser::FftAnalyser( IObserver& observer, double ampCutoff, double bindCutoff )
: core::Analyser( observer ),
  mPlan( NULL ),
  mAmplitudeCutoff( ampCutoff ),
  mBindCutoff( bindCutoff ),
  mFreqs( NULL ),
  mMags( NULL ),
  mAngles( NULL )
{
}

bool FftAnalyser::init( const char* name, unsigned int rate,
                        unsigned int bufferSize, unsigned int captureSize )
{
    // Make sure sizes are valid.
    if( bufferSize != captureSize )
        return false;

    // Initialize parent first.
    if( !Analyser::init( name, rate, bufferSize, captureSize ) )
        return false;

    // Allocate the array for frequencies.
    mFreqs = (double*)::fftw_malloc( sizeof( double ) * this->bufferSize() );

    // We ignore DC and Nyqist frequency.
    const size_t size = ( this->bufferSize() - 1 ) / 2;

    mMags   = new double[ size ];
    mAngles = new Angle[ size ];

    // Setup the plan.
    mPlan = ::fftw_plan_r2r_1d( this->bufferSize(), mSamples, mFreqs,
                                FFTW_R2HC, FFTW_MEASURE );
    if( NULL == mPlan )
        return false;

    return true;
}

void FftAnalyser::free()
{
    // Release the plan.
    util::safeRelease( mPlan,  ::fftw_destroy_plan );
    util::safeRelease( mFreqs, ::fftw_free );

    util::safeDeleteArray( mMags );
    util::safeDeleteArray( mAngles );

    // Let the parent free too.
    Analyser::free();
}

bool FftAnalyser::step()
{
    // Let parent process first
    if( !Analyser::step() )
        return false;

    // Compute frequencies
    if( !computeFreqs() )
        return false;

    // Process the frequencies
    if( !processFreqs() )
        return false;

    return true;
}

bool FftAnalyser::reset()
{
    // TODO: reset all angles.
    return true;
}

double FftAnalyser::getFreq( double index ) const
{
    return index * sampleRate() / bufferSize();
}

bool FftAnalyser::checkAmplitude( size_t index ) const
{
    return amplitudeCutoff() <= getMag( index );
}

bool FftAnalyser::checkLocalMax( size_t index ) const
{
    // Ignore DC and Nyquist frequency.
    const size_t size = ( bufferSize() - 1 ) / 2;

    if( 0 == index )
        // Ignore DC entirely
        return false;
    else if( size < index )
        // Ignore Nyquist entirely
        return false;

    if( 1 == index )
        // Don't consider DC
        return getMag( index + 1 ) < getMag( index );
    else if( size < index + 1 )
        // Don't consider Nyquist
        return getMag( index - 1 ) < getMag( index );

    // Consider both previous and next frequency
    return getMag( index - 1 ) < getMag( index )
        && getMag( index + 1 ) < getMag( index );
}

bool FftAnalyser::checkBound( size_t index, size_t boundIndex )
{
    return bindCutoff() <= 10 * ::log10( getMag( boundIndex ) / getMag( index ) );
}

bool FftAnalyser::computeFreqs()
{
    // Ignore DC and Nyquist frequency.
    const size_t size = ( bufferSize() - 1 ) / 2;

    // Execute the plan
    ::fftw_execute( mPlan );

    // Compute magnitude for each frequency.
    for( size_t index = 0; index < size; ++index )
    {
        const double real = getReal( index + 1 );
        const double img  = getImg( index + 1 );

        mMags[ index ] = ::sqrt( real * real + img * img );
    }

    return true;
}

bool FftAnalyser::processFreqs()
{
    // Ignore DC and Nyquist frequency.
    const size_t size = ( bufferSize() - 1 ) / 2;

    // Clear the observer.
    observer().clear();

    // Do magic on each frequency.
    for( size_t index = 0; index < size; ++index )
    {
        Angle& angle = getAngle( index + 1 );

        // if( index != 10 )
        // if( !checkAmplitude( index + 1 ) || !checkLocalMax( index + 1 ) )
        if( !checkAmplitude( index + 1 ) )
            // Doesn't fulfill the requirements.
            angle.reset();
        else if( checkLocalMax( index + 1 ) )
        {
            // ::printf( "%10.4f (%10.4f) %10.4f | ",
            //           getMag( index ),
            //           getMag( index + 1 ),
            //           getMag( index + 2 ) );

            // Update the angle.
            angle.update( ::atan2( getImg( index + 1 ),
                                   getReal( index + 1 ) ) );

            const size_t boundIndex =
                getMag( index ) < getMag( index + 2 )
                ? index + 2
                : index;

            if( checkBound( index + 1, boundIndex ) )
            {
                Angle& boundAngle = getAngle( boundIndex );

                // Update the bound angle.
                boundAngle.update( ::atan2( getImg( boundIndex ),
                                            getReal( boundIndex ) ) );

                // ::printf( "[%05lu+%05lu] "
                //           "%10.4f (%10.4f) "
                //           "%10.4f (%10.4f) | ",
                //           index + 1, boundIndex,
                //           index + 1 + angle.frequency(),
                //           getFreq( index + 1 + angle.frequency() ),
                //           boundIndex + boundAngle.frequency(),
                //           getFreq( boundIndex + boundAngle.frequency() ) );

                if( angle.ready() )
                    if( boundAngle.ready() )
                        if( 0 < angle.frequency() / boundAngle.frequency() )
                            if( 0 < angle.frequency() / signed( boundIndex - index - 1 ) )
                                observer().add( getFreq( index + 1 + angle.frequency() ) );
                            else
                                observer().add( getFreq( boundIndex + boundAngle.frequency() ) );
                        else
                            ; // ::printf( "%10.4f X %10.4f => ALIAS\n",
                            //           index + 1 + angle.frequency(),
                            //           boundIndex + boundAngle.frequency() );
                    else /* !boundAngle.ready() */
                        observer().add( getFreq( index + 1 + angle.frequency() ) );
                else /* !angle.ready() */
                    if( boundAngle.ready() )
                        observer().add( getFreq( boundIndex + boundAngle.frequency() ) );
                    // ... else neither of the frequencies is ready.
                    else
                        ;// ::puts( "NEITHER READY" );
            }
            else /* !checkBound( index, boundIndex ) */
            {
                if( angle.ready() )
                {
                    const double freqIndex = index + 1 + angle.frequency();

                    // ::printf( "[   %05lu   ] "
                    //           "%10.4f %10.4f %10.4f | "
                    //           "%10.4f"            " | ",
                    //           index + 1,
                    //           getMag( index ), getMag( index + 1 ), getMag( index + 2 ),
                    //           freqIndex );

                    observer().add( getFreq( freqIndex ) );
                }
            }
        }
    }

    return true;
}

// bool FftAnalyser::processSingleFreq( size_t index )
// {
//     // const double freq =
//     //     (double)( index + 1 )
//     //     * (double)sampleRate()
//     //     / (double)bufferSize();

//     // Angle& ang = mAngles[ index ];

//     return true;
// }

// bool FftAnalyser::processBoundFreq( size_t index, size_t boundIndex )
// {
//     const double freq = (double)index * (double)sampleRate() / (double)bufferSize();

//     const double cur  = mMags[ index ];
//     const double prev = mMags[ index - 1 ];
//     const double next = mMags[ index + 1 ];

//     Angle& ang = mAngles[ index ];

//     // Check if the amplitude is big enough and a local max
//     if( amplitudeCutoff() < cur
//         && prev < cur && cur > next )
//     {
//         // Compute current angle.
//         const double angle = ::atan2( mFreqs[ bufferSize() - index ],
//                                       mFreqs[ index ] );

//         // Update the angle information.
//         ang.update( angle );

//         // Determine which neighbor in bigger in magnitude.
//         size_t boundIndex = index - 1;
//         double boundValue = prev;

//         if( boundValue < next )
//         {
//             boundIndex = index + 1;
//             boundValue = next;
//         }

//         // Determine if the frequencies are bound.
//         if( bindCutoff() <= 10 * ::log10( boundValue / cur ) )
//         {
//             // Compute current bound angle.
//             const double boundAngle = ::atan2( mFreqs[ bufferSize() - boundIndex ],
//                                                mFreqs[ boundIndex ] );

//             // Update the bound angle information.
//             mAngles[ boundIndex ].update( boundAngle );
//         }
//         else
//         {
//             // Notify observer of the frequency.
//             observer().add( freq + ang.frequency() );
//         }
//     }
//     else
//     {
//         // The frequency is not present, reset.
//         ang.reset();
//     }

//     return true;
// }

/*************************************************************************/
/* core::FftAnalyser::Angle                                              */
/*************************************************************************/
FftAnalyser::Angle::Angle()
: mCounter( new stats::Derivative< double, double >(
                new stats::Periodic< double, double >(
                    new stats::AverageRing< double, double >( 24 ),
                    2 * M_PI ) ) )
{
}

FftAnalyser::Angle::~Angle()
{
    util::safeDelete( mCounter );
}

bool FftAnalyser::Angle::ready() const
{
    return mCounter->ready();
}

double FftAnalyser::Angle::frequency() const
{
    return mCounter->result() / ( 2 * M_PI );
}

void FftAnalyser::Angle::update( double angle )
{
    mCounter->add( angle );
}

void FftAnalyser::Angle::reset()
{
    mCounter->reset();
}
