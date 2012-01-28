/**
 * @file core/Analyser.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CORE__ANALYSER_H__INCL__
#define __CGT__CORE__ANALYSER_H__INCL__

#include "alsa/Pcm.h"

namespace cgt {
/**
 * @brief Core code of CGT.
 *
 * @author Bloody.Rabbit
 */
namespace core {

/**
 * @brief Base class for signal analysers.
 *
 * @author Bloody.Rabbit
 */
class Analyser
{
public:
    /**
     * @brief An observer of an analyser.
     *
     * @author Bloody.Rabbit
     */
    class IObserver
    {
    public:
        /**
         * @brief Start a new analysis run.
         *
         * Callee should consider all previously
         * detected frequencies invalid.
         */
        virtual void start() = 0;
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
         * @brief Ends a new analysis run.
         *
         * No new data will be added until another
         * call to start().
         */
        virtual void end() = 0;
    };

    /**
     * @brief The primary constructor.
     *
     * @param[in] observer The observer.
     */
    Analyser( IObserver& observer );
    /**
     * @brief Releases acquired resources.
     */
    virtual ~Analyser();

    /**
     * @brief Obtains current sample rate.
     *
     * @return Current sample rate.
     */
    unsigned int sampleRate() const { return mSampleRate; }
    /**
     * @brief Obtains current buffer size.
     *
     * @return Current buffer size.
     */
    unsigned int bufferSize() const { return mBufferSize; }
    /**
     * @brief Obtains current capture size.
     *
     * @return Current capture size.
     */
    unsigned int captureSize() const { return mCaptureSize; }

    /**
     * @brief Obtains current observer.
     *
     * @return Current observer.
     */
    IObserver& observer() const { return *mObserver; }
    /**
     * @brief Sets new observer.
     *
     * @param[in] observer The new observer.
     */
    void setObserver( IObserver& observer ) { mObserver = &observer; }

    /**
     * @brief Initializes the analyser.
     *
     * @param[in] name        Name of the PCM.
     * @param[in] rate        The sample rate to use.
     * @param[in] bufferSize  The size of the sample buffer.
     * @param[in] captureSize The sample capture size.
     */
    virtual void init( const char* name, unsigned int rate,
                       unsigned int bufferSize, unsigned int captureSize );
    /**
     * @brief Frees the analyser resources.
     */
    virtual void free();

    /**
     * @brief Runs a step in the process.
     */
    virtual void step() { ( this->* ( CAPTURE_ROUTINES[ mCapture ] ) )(); }
    /**
     * @brief Resets the process.
     */
    virtual void reset();

protected:
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
     * @brief Fills the buffer entirely.
     *
     * Any previous captured content is overwritten.
     */
    void captureFull();
    /**
     * @brief Captures only a bit.
     */
    void captureStep();

    /// The bound observer.
    IObserver* mObserver;
    /// The underlying PCM.
    alsa::Pcm* mPcm;

#ifdef CGT_DEBUG_ANALYSIS_FREQ
    /// Current phase.
    double mPhase;
#endif /* CGT_DEBUG_ANALYSIS_FREQ */

    /// Current capture state.
    Capture mCapture;

    /// Current sample rate.
    unsigned int mSampleRate;
    /// Size of the sample buffer.
    unsigned int mBufferSize;
    /// The sample capture size.
    unsigned int mCaptureSize;

    /// The sample buffer.
    double* mSamples;

    /// Capture state routine table.
    static void ( Analyser::* CAPTURE_ROUTINES[] )();
};

}} // cgt::core

#endif /* !__CGT__CORE__ANALYSER_H__INCL__ */
