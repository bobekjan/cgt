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
     * @param[in] ampCutoff  The amplitude cutoff value.
     * @param[in] bindCutoff The bind cutoff value [dB].
     */
    FftAnalyser( IObserver& observer, double ampCutoff, double bindCutoff );

    /**
     * @brief Obtains current amplitude cutoff value.
     *
     * @return Current amplitude cutoff value.
     */
    double amplitudeCutoff() const { return mAmplitudeCutoff; }
    /**
     * @brief Obtains current bind cutoff value [dB].
     *
     * @return Current bind cutoff value [dB].
     */
    double bindCutoff() const { return mBindCutoff; }

    /**
     * @brief Sets new amplitude cutoff value.
     *
     * @param[in] ampCutoff New amplitude cutoff value.
     */
    void setAmplitudeCutoff( double ampCutoff ) { mAmplitudeCutoff = ampCutoff; }
    /**
     * @brief Sets new bind cutoff value [dB].
     *
     * @param[in] bindCutoff New bind cutoff value [dB].
     */
    void setBindCutoff( double bindCutoff ) { mBindCutoff = bindCutoff; }

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
    class Angle
    {
    public:
        /**
         * @brief Primary constructor.
         */
        Angle();
        /**
         * @brief Destroys the counter.
         */
        ~Angle();

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
         * @brief Computes approximate fractional frequency.
         *
         * @return The frequency.
         */
        double frequency() const;

        /**
         * @brief Updates the information with new data.
         *
         * @param[in] angle The angle to update with.
         */
        void update( double angle );
        /**
         * @brief Resets all the information.
         */
        void reset();

    protected:
        /// The statistics counter.
        stats::ICounter< double, double >* mCounter;
    };

    /**
     * @brief Obtains real part of a frequency.
     *
     * @param[in] index Index of the frequency.
     *
     * @return The real part of the frequency.
     */
    double getReal( size_t index ) const { return mFreqs[ index ]; }
    /**
     * @brief Obtains imaginary part of a frequency.
     *
     * @param[in] index Index of the frequency.
     *
     * @return The imaginary part of the frequency.
     */
    double getImg( size_t index ) const { return mFreqs[ mBufferSize - index ]; }
    /**
     * @brief Obtains magnitude of a frequency.
     *
     * @param[in] index Index of the frequency
     *
     * @return Magnitude of the frequency.
     */
    double getMag( size_t index ) const { return mMags[ index - 1 ]; }
    /**
     * @brief Obtains Angle object of a frequency.
     *
     * @param[in] index Index of the frequency.
     *
     * @return The Angle object of the frequency.
     */
    Angle& getAngle( size_t index ) const { return mAngles[ index - 1 ]; }

    /**
     * @brief Obtains actual frequency of a frequency index.
     *
     * @param[in] index Index of the frequency.
     *
     * @return The actual frequency.
     */
    double getFreq( double index ) const;
    /**
     * @brief Check if the frequency amplitude is large enough.
     *
     * @param[in] index Index of the frequency.
     *
     * @retval true  The amplitude is large enough.
     * @retval false The amplitude is not large enough.
     */
    bool checkAmplitude( size_t index ) const;
    /**
     * @brief Checks if the frequency is a local maximum.
     *
     * @param[in] index Index of the frequency.
     *
     * @retval true  The frequency is a local maximum.
     * @retval false The frequency is not a local maximum.
     */
    bool checkLocalMax( size_t index ) const;
    /**
     * @brief Checks if the frequencies are bound.
     *
     * @param[in] index      Index of the frequency.
     * @param[in] boundIndex Index of the other frequency.
     *
     * @retval true  The frequencies are bound.
     * @retval false The frequencies are not bound.
     */
    bool checkBound( size_t index, size_t boundIndex );

    /**
     * @brief Compute frequency magnitudes.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool computeFreqs();
    /**
     * @brief Processes frequencies.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool processFreqs();

    /**
     * @brief Processes a single frequency.
     *
     * @param[in] index Index of the frequency.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    // bool processSingleFreq( size_t index );
    /**
     * @brief Processes a bound frequency.
     *
     * @param[in] index      Index of the frequency.
     * @param[in] boundIndex Index of the bound frequency.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    // bool processBoundFreq( size_t index, size_t boundIndex );

    /// Our FFTW plan.
    fftw_plan mPlan;

    /// The amplitude cutoff.
    double mAmplitudeCutoff;
    /// The bind cutoff [dB].
    double mBindCutoff;

    /// Result of the FFT.
    double* mFreqs;
    /// Computed magnitudes.
    double* mMags;
    /// Angle information of each frequency.
    Angle*  mAngles;
};

}} // cgt::core

#endif /* !__CGT__CORE__FFT_ANALYSER_H__INCL__ */
