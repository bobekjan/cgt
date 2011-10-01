/**
 * @file alsa/Error.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* alsa::Error                                                           */
/*************************************************************************/
Error::Error( int code )
: mCode( code )
{
}

const char* Error::what() const
{
    return ::snd_strerror( code() );
}
