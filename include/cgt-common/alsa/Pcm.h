/**
 * @file alsa/Pcm.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__ALSA__PCM_H__INCL__
#define __CGT__ALSA__PCM_H__INCL__

namespace cgt { namespace alsa {

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
    Pcm();
    /**
     * @brief The primary constructor, opens a PCM.
     *
     * @param[in] name   Name of the PCM.
     * @param[in] stream The wanted stream.
     * @param[in] mode   Open mode.
     */
    Pcm( const char* name, snd_pcm_stream_t stream, int mode );
    /**
     * @brief Closes the PCM handle.
     */
    ~Pcm();

    /**
     * @brief Opens a PCM.
     *
     * Implemented by <code>snd_pcm_open</code>.
     *
     * @param[in] name   Name of the PCM.
     * @param[in] stream The wanted stream.
     * @param[in] mode   Open mode.
     */
    void open( const char* name, snd_pcm_stream_t stream, int mode );
    /**
     * @brief Closes the PCM.
     *
     * Implemented by <code>snd_pcm_close</code>.
     */
    void close();

    /**
     * @brief Sets required PCM params.
     *
     * Implemented by <code>snd_pcm_set_params</code>.
     *
     * @param[in] format   Required PCM format.
     * @param[in] access   Required PCM access.
     * @param[in] channels Required number of channels.
     * @param[in] rate     Required sample rate [Hz].
     * @param[in] resample Allow software resampling in alsa-lib.
     * @param[in] latency  Required overall latency [us].
     */
    void setParams( snd_pcm_format_t format, snd_pcm_access_t access,
                    unsigned int channels, unsigned int rate,
                    int resample, unsigned int latency );
    /**
     * @brief Recovers the PCM from previous error.
     *
     * Implemented by <code>snd_pcm_recover</code>.
     *
     * @param[in] err    The previous error code.
     * @param[in] silent Suppress printing of an error message.
     */
    void recover( int code, int silent );

    /**
     * @brief Reads interleaved samples from the PCM.
     *
     * Implemented by <code>snd_pcm_readi</code>.
     *
     * @param[out] buffer Where to store the samples.
     * @param[in]  size   Number of frames to be read.
     *
     * @return Number of frames read.
     */
    snd_pcm_sframes_t readInt( void* buffer, snd_pcm_uframes_t size );
    /**
     * @brief Writes interleaved samples to the PCM.
     *
     * Implemented by <code>snd_pcm_writei</code>.
     *
     * @param[in] buffer A buffer containing the samples.
     * @param[in] size   Number of frames to be written.
     *
     * @return Number of frames written.
     */
    snd_pcm_sframes_t writeInt( const void* buffer, snd_pcm_uframes_t size );

    /**
     * @brief Reads noninterleaved samples from the PCM.
     *
     * Implemented by <code>snd_pcm_readn</code>.
     *
     * @param[out] buffers Where to store the samples.
     * @param[in]  size    Number of frames to be read.
     *
     * @return Number of frames read.
     */
    snd_pcm_sframes_t readNonint( void** buffers, snd_pcm_uframes_t size );
    /**
     * @brief Writes noninterleaved samples to the PCM.
     *
     * Implemented by <code>snd_pcm_writen</code>.
     *
     * @param[in] buffers Buffers with samples for each channel.
     * @param[in] size    Number of frames to be written.
     *
     * @return Number of frames written.
     */
    snd_pcm_sframes_t writeNonint( void** buffers, snd_pcm_uframes_t size );

protected:
    /// The wrapped struct.
    snd_pcm_t* mPcm;
};

// Simple wrapper, all methods are inlined.
#include "alsa/Pcm.inl"

}} // cgt::alsa

#endif /* !__CGT__ALSA__PCM_H__INCL__ */
