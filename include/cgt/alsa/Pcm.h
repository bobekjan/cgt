/**
 * @file alsa/Pcm.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __ALSA__PCM_H__INCL__
#define __ALSA__PCM_H__INCL__

#include "alsa/Error.h"

namespace alsa {

/**
 * @brief An ALSA PCM device.
 *
 * Wraps <code>struct snd_pcm_t</code>.
 *
 * @author Bloody.Rabbit
 */
class Pcm
{
public:
    /**
     * @brief The default constructor.
     */
    Pcm() : mPcm( NULL ) {}
    /**
     * @brief The primary constructor, opens a PCM.
     *
     * @param[in] name   Name of the PCM.
     * @param[in] stream The wanted stream.
     * @param[in] mode   Open mode.
     */
    Pcm( const char* name, snd_pcm_stream_t stream, int mode ) : mPcm( NULL )
    { const Error err = open( name, stream, mode ); assert( !err ); }
    /**
     * @brief Closes the PCM handle.
     */
    ~Pcm() { const Error err = close(); assert( !err ); }

    /**
     * @brief Opens a PCM.
     *
     * @param[in] name   Name of the PCM.
     * @param[in] stream The wanted stream.
     * @param[in] mode   Open mode.
     *
     * @return An error code.
     */
    Error open( const char* name, snd_pcm_stream_t stream, int mode )
    { return ::snd_pcm_open( &mPcm, name, stream, mode ); }
    /**
     * @brief Closes the PCM.
     *
     * @return An error code.
     */
    Error close() { return ::snd_pcm_close( mPcm ); }

    /**
     * @brief Sets required PCM params.
     *
     * @param[in] format   Required PCM format.
     * @param[in] access   Required PCM access.
     * @param[in] channels Required number of channels.
     * @param[in] rate     Required sample rate [Hz].
     * @param[in] resample Allow software resampling in alsa-lib.
     * @param[in] latency  Required overall latency [us].
     *
     * @return An error code.
     */
    Error setParams( snd_pcm_format_t format, snd_pcm_access_t access,
                     unsigned int channels, unsigned int rate,
                     int resample, unsigned int latency )
    { return ::snd_pcm_set_params( mPcm, format, access, channels, rate, resample, latency ); }
    /**
     * @brief Recovers the PCM from previous error.
     *
     * @param[in] err    The previous error.
     * @param[in] silent Suppress printing of an error message.
     *
     * @return An error code.
     */
    Error recover( const Error& err, int silent )
    { return ::snd_pcm_recover( mPcm, err.code(), silent ); }

    /**
     * @brief Writes interleaved samples to the PCM.
     *
     * @param[in] buffer A buffer containing the samples.
     * @param[in] size   Number of frames to be written.
     *
     * @return Number of frames written or a negative error code.
     */
    snd_pcm_sframes_t writeInt( const void* buffer, snd_pcm_uframes_t size )
    { return ::snd_pcm_writei( mPcm, buffer, size ); }

protected:
    /// The wrapped struct.
    snd_pcm_t* mPcm;
};

}

#endif /* !__ALSA__PCM_H__INCL__ */
