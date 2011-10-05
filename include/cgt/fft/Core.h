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

/**
 * @brief Core class of FFT.
 *
 * @author Bloody.Rabbit
 */
class Core
{
public:
    class IObserver;

    /**
     * @brief Performs basic initialization.
     *
     * @param[in] observer The observer.
     */
    Core( IObserver& observer );
    /**
     * @brief Releases resources.
     */
    ~Core();

    /**
     * @brief Initializes underlying PCM.
     *
     * @param[in] name Name of the PCM.
     * @param[in] rate The sample rate to use.
     *
     * @retval true  Initialization succeeded.
     * @retval false Initialization failed.
     */
    bool initPcm( const char* name, unsigned int rate );
    /**
     * @brief Frees the underlying PCM.
     */
    void freePcm();

    /**
     * @brief Runs the first step.
     *
     * Can also be used to reset the transform.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool stepFirst();
    /**
     * @brief Runs the next step.
     *
     * Keep in mind that <code>stepFirst()</code>
     * must be called first.
     *
     * @retval true  Step succeeded.
     * @retval false Step failed.
     */
    bool stepNext();

protected:
    /// The bound observer.
    IObserver* mObserver;

    // The underlying PCM.
    alsa::Pcm* mPcm;
};

}

#endif /* !__FFT__CORE_H__INCL__ */
