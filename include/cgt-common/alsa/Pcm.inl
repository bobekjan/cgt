/**
 * @file alsa/Pcm.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* cgt::alsa::Pcm                                                        */
/*************************************************************************/
inline Pcm::Pcm()
: mPcm( NULL )
{
}

inline Pcm::Pcm( const char* name, snd_pcm_stream_t stream, int mode )
: mPcm( NULL )
{
    // Open the PCM device
    open( name, stream, mode );
}

inline Pcm::~Pcm()
{
    // Close the PCM device
    close();
}

inline void Pcm::open( const char* name, snd_pcm_stream_t stream, int mode )
{
    // Open the device
    int code = ::snd_pcm_open( &mPcm, name, stream, mode );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to open PCM device '%s': %s",
                        name, ::snd_strerror( code ) ) );
}

inline void Pcm::close()
{
    // Close the device
    int code = ::snd_pcm_close( mPcm );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to close PCM device: %s",
                        ::snd_strerror( code ) ) );
}

inline void Pcm::setParams( snd_pcm_format_t format, snd_pcm_access_t access,
                            unsigned int channels, unsigned int rate,
                            int resample, unsigned int latency )
{
    // Set the parameters
    int code = ::snd_pcm_set_params( mPcm, format, access, channels, rate, resample, latency );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to set parameters of PCM device: %s",
                        ::snd_strerror( code ) ) );
}

inline void Pcm::recover( int err, int silent )
{
    // Recover the device
    int code = ::snd_pcm_recover( mPcm, err, silent );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to recover PCM device: %s",
                        ::snd_strerror( code ) ) );
}

inline snd_pcm_sframes_t Pcm::readInt( void* buffer, snd_pcm_uframes_t size )
{
    // Read the frames
    snd_pcm_sframes_t code = ::snd_pcm_readi( mPcm, buffer, size );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to read interleaved samples: %s",
                        ::snd_strerror( code ) ) );

    // Return number of read samples
    return code;
}

inline snd_pcm_sframes_t Pcm::writeInt( const void* buffer, snd_pcm_uframes_t size )
{
    // Write the frames
    snd_pcm_sframes_t code = ::snd_pcm_writei( mPcm, buffer, size );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to write interleaved samples: %s",
                        ::snd_strerror( code ) ) );

    // Return number of written samples
    return code;
}

inline snd_pcm_sframes_t Pcm::readNonint( void** buffers, snd_pcm_uframes_t size )
{
    // Read the frames
    snd_pcm_sframes_t code = ::snd_pcm_readn( mPcm, buffers, size );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to read non-interleaved samples: %s",
                        ::snd_strerror( code ) ) );

    // Return the number of read samples
    return code;
}

inline snd_pcm_sframes_t Pcm::writeNonint( void** buffers, snd_pcm_uframes_t size )
{
    // Write the frames
    snd_pcm_sframes_t code = ::snd_pcm_writen( mPcm, buffers, size );

    // Check for error
    if( 0 > code )
        // Throw an error message
        throw std::runtime_error(
            ::ssprintf( "Failed to write non-interleaved samples: %s",
                        ::snd_strerror( code ) ) );

    // Return the number of written samples
    return code;
}
