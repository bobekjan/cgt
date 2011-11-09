/**
 * @file fft/Core.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __FFT__CORE_H__INCL__
#define __FFT__CORE_H__INCL__

#include "alsa/Pcm.h"

namespace fft {

#define DEBUG_FFT 1

/**
 * @brief Core class of FFT.
 *
 * @author Bloody.Rabbit
 */
class Core
{
public:
    /**
     * @brief An observer of the FFT core.
     *
     * @author Bloody.Rabbit
     */
    class IObserver
    {
    public:
        /**
         * @brief Adds a frequency.
         *
         * Called whenever a frequency is successfully
         * detected in the incoming signal.
         *
         * @param[in] freq The detected frequency [Hz].
         */
        virtual void add( double freq ) = 0;
        /**
         * @brief Clears frequencies.
         *
         * Called when new analysis begins; callee
         * should consider all previously detected
         * frequencies invalid.
         */
        virtual void clear() = 0;
    };

    /**
     * @brief Performs basic initialization.
     *
     * @param[in] observer   The observer.
     * @param[in] ampCutoff  The amplitude cutoff value.
     * @param[in] bindCutoff The bind cutoff value [dB].
     */
    Core( IObserver& observer, double ampCutoff, double bindCutoff );
    /**
     * @brief Releases resources.
     */
    ~Core();

    /**
     * @brief Obtains current observer.
     *
     * @return Current observer.
     */
    IObserver& observer() const { return *mObserver; }
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
     * @brief Sets new observer.
     *
     * @param[in] observer The new observer.
     */
    void setObserver( IObserver& observer ) { mObserver = &observer; }
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
     * @brief Initializes underlying PCM.
     *
     * @param[in] name        Name of the PCM.
     * @param[in] rate        The sample rate to use.
     * @param[in] bufferSize  The size of the sample buffer.
     * @param[in] captureSize The sample capture size.
     *
     * @retval true  Initialization succeeded.
     * @retval false Initialization failed.
     */
    bool initPcm( const char* name, unsigned int rate,
                  unsigned int bufferSize, unsigned int captureSize );
    /**
     * @brief Frees the underlying PCM.
     */
    void freePcm();

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
     * @brief Helper class of fft::Core.
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
         * @brief Checks if the object is active.
         *
         * It basically means that calling frequency() will
         * yield reasonable value, not division by zero.
         *
         * @retval true  Object is active.
         * @retval false Object is inactive.
         */
        bool active() const { return 2 <= mSamples; }
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
        /// Current angle.
        double       mAngle;
        /// Sum of all computed angle velocities.
        double       mAvSum;
        /// Number of samples so far.
        unsigned int mSamples;
    };

    /**
     * @brief Describes current capture state.
     *
     * @author Bloody.Rabbit
     */
    enum Capture
    {
        CAPTURE_FULL, //< A full capture pending.
        CAPTURE_STEP  //< A step capture pending.
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
    double getFreq( size_t index ) const;
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
     * @brief Fills the buffer entirely.
     *
     * Any previous captured content is overwritten.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool captureFull();
    /**
     * @brief Captures only a bit.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool captureStep();

    /**
     * @brief Executes the FFTW plan.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool executePlan();
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
    bool processSingleFreq( size_t index );
    /**
     * @brief Processes a bound frequency.
     *
     * @param[in] index      Index of the frequency.
     * @param[in] boundIndex Index of the bound frequency.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool processBoundFreq( size_t index, size_t boundIndex );

    /// The bound observer.
    IObserver* mObserver;
    /// The underlying PCM.
    alsa::Pcm* mPcm;
    /// Our FFTW plan.
    fftw_plan  mPlan;

#ifdef DEBUG_FFT
    /// Current sin step.
    unsigned short mStep;
#endif /* DEBUG_FFT */

    /// Current capture state.
    Capture mCapture;

    /// Current sample rate.
    unsigned int mSampleRate;
    /// Size of the sample buffer.
    unsigned int mBufferSize;
    /// The sample capture size.
    unsigned int mCaptureSize;
    /// The amplitude cutoff.
    double       mAmplitudeCutoff;
    /// The bind cutoff [dB].
    double       mBindCutoff;

    /// The sample buffer.
    double* mSamples;
    /// Result of the FFT.
    double* mFreqs;
    /// Computed magnitudes.
    double* mMags;
    /// Angle information of each frequency.
    Angle*  mAngles;

    /// Capture state routine table.
    static bool ( Core::* CAPTURE_ROUTINES[] )();
};

} // fft

#endif /* !__FFT__CORE_H__INCL__ */
