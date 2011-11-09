/**
 * @file alsa/Pcm.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* alsa::Pcm                                                             */
/*************************************************************************/
inline Pcm::Pcm()
: mPcm( NULL )
{
}

inline Pcm::Pcm( const char* name, snd_pcm_stream_t stream, int mode )
: mPcm( NULL )
{
    const Error err = open( name, stream, mode );
    assert( !err );
}

inline Pcm::~Pcm()
{
    const Error err = close();
    assert( !err );
}

inline Error Pcm::open( const char* name, snd_pcm_stream_t stream, int mode )
{
    return ::snd_pcm_open( &mPcm, name, stream, mode );
}

inline Error Pcm::close()
{
    return ::snd_pcm_close( mPcm );
}

inline Error Pcm::setParams( snd_pcm_format_t format, snd_pcm_access_t access,
                             unsigned int channels, unsigned int rate,
                             int resample, unsigned int latency )
{
    return ::snd_pcm_set_params( mPcm, format, access, channels, rate, resample, latency );
}

inline Error Pcm::recover( const Error& err, int silent )
{
    return ::snd_pcm_recover( mPcm, err.code(), silent );
}

inline snd_pcm_sframes_t Pcm::readInt( void* buffer, snd_pcm_uframes_t size )
{
    return ::snd_pcm_readi( mPcm, buffer, size );
}

inline snd_pcm_sframes_t Pcm::writeInt( const void* buffer, snd_pcm_uframes_t size )
{
    return ::snd_pcm_writei( mPcm, buffer, size );
}

inline snd_pcm_sframes_t Pcm::readNonint( void** buffers, snd_pcm_uframes_t size )
{
    return ::snd_pcm_readn( mPcm, buffers, size );
}

inline snd_pcm_sframes_t Pcm::writeNonint( void** buffers, snd_pcm_uframes_t size )
{
    return ::snd_pcm_writen( mPcm, buffers, size );
}
