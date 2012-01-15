/**
 * @file core/FftAnalyser.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CORE__FFT_ANALYSER_H__INCL__
#define __CGT__CORE__FFT_ANALYSER_H__INCL__

#include "core/Analyser.h"
#include "stats/AverageRing.h"
#include "stats/Derivative.h"
#include "stats/Periodic.h"

namespace cgt { namespace core {

/**
 * @brief Core class of FFT.
 *
 * @author Bloody.Rabbit
 */
class FftAnalyser
: public Analyser
{
public:
    /**
     * @brief Performs basic initialization.
     *
     * @param[in] observer   The observer.
     * @param[in] magCutoff  The magnitude cutoff value.
     */
    FftAnalyser( IObserver& observer, double magCutoff );

    /**
     * @brief Obtains current magnitude cutoff value.
     *
     * @return Current magnitude cutoff value.
     */
    double magnitudeCutoff() const { return mMagnitudeCutoff; }

    /**
     * @brief Sets new magnitude cutoff value.
     *
     * @param[in] ampCutoff New magnitude cutoff value.
     */
    void setMagnitudeCutoff( double ampCutoff ) { mMagnitudeCutoff = ampCutoff; }

    /**
     * @brief Initializes the analyser.
     *
     * @param[in] name        Name of the PCM.
     * @param[in] rate        The sample rate to use.
     * @param[in] bufferSize  The size of the sample buffer.
     * @param[in] captureSize The sample capture size.
     *
     * @retval true  Initialization succeeded.
     * @retval false Initialization failed.
     */
    bool init( const char* name, unsigned int rate,
               unsigned int bufferSize, unsigned int captureSize );
    /**
     * @brief Frees the analyser resources.
     */
    void free();

    /**
     * @brief Runs a step in the process.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool step();
    /**
     * @brief Resets the process.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool reset();

protected:
    /**
     * @brief Helper class of FftAnalyser.
     *
     * Holds information about a particular frequency.
     *
     * @author Bloody.Rabbit
     */
    class Frequency
    {
    public:
        /**
         * @brief Primary constructor.
         *
         * @param[in] limit Number of samples to average from.
         */
        Frequency( unsigned int limit = 64 );
        /**
         * @brief Destroys the counter.
         */
        ~Frequency();

        /**
         * @brief Checks if the object is ready.
         *
         * It basically means that calling frequency() will
         * yield reasonable value, not division by zero.
         *
         * @retval true  Object is ready.
         * @retval false Object is not ready.
         */
        bool ready() const;
        /**
         * @brief Obtains current magnitude.
         *
         * @return The magnitude.
         */
        double magnitude() const { return mMagnitude; }
        /**
         * @brief Computes approximate fractional frequency.
         *
         * @return The frequency.
         */
        double frequency() const;
        /**
         * @brief Obtains current local max count.
         *
         * @return The local max count.
         */
        unsigned int localMax() const { return mLocalMaxCount; }

        /**
         * @brief Updates the magnitude with new data.
         *
         * @param[in] real Real part of the FFT output.
         * @param[in] img  Imaginary part of the FFT output.
         */
        void updateMagnitude( double real, double img ) { mMagnitude = ::sqrt( real * real + img * img ); }
        /**
         * @brief Updates the information with new data.
         *
         * @param[in] angle Angle of the frequency.
         */
        void updateFrequency( double angle );
        /**
         * @brief Update the local max.
         */
        void updateLocalMax() { ++mLocalMaxCount; }

        /**
         * @brief Resets all the information.
         */
        void reset();

    protected:
        /// Current magnitude.
        double mMagnitude;

        /// The statistics counter for frequency correction.
        stats::ICounter< double, double >* mCounter;
        /// Number of times this has been a local max.
        unsigned int mLocalMaxCount;
    };

    /**
     * @brief Obtains Frequency object of a frequency.
     *
     * @param[in] index Index of the frequency.
     *
     * @return The Frequency object of the frequency.
     */
    Frequency& frequency( size_t index ) const { return mFreqs[ index ]; }
    /**
     * @brief Obtains number of frequencies.
     *
     * @return The number of frequencies.
     */
    size_t frequencyCount() const { return ( bufferSize() - 1 ) / 2; }

    /**
     * @brief Processes frequencies.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool processFreqs();
    /**
     * @brief Processes local maxes.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool processLocalMax();
    /**
     * @brief Processes output.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool processOutput();

    /// Our FFTW plan.
    fftw_plan mPlan;

    /// The magnitude cutoff.
    double mMagnitudeCutoff;

    /// Result of the FFT.
    double*    mFftOutput;
    /// Information of each frequency.
    Frequency* mFreqs;
};

}} // cgt::core

#endif /* !__CGT__CORE__FFT_ANALYSER_H__INCL__ */
