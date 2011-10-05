/**
 * @file fft/Core.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt.h"
#include "fft/Core.h"

using namespace fft;

/*************************************************************************/
/* fft::Core                                                             */
/*************************************************************************/
Core::Core( IObserver* observer )
: mObserver( observer ),
  mPcm( NULL )
{
}

Core::~Core()
{
    // Free the PCM.
    freePcm();
}

bool Core::initPcm( const char* name, unsigned int rate )
{
    // Make sure the PCM is not initialized.
    freePcm();
    mPcm = new alsa::Pcm( name, SND_PCM_STREAM_CAPTURE, 0 );

    // We want doubles of one channel at the given rate.
    return mPcm.setParams( SND_PCM_FORMAT_FLOAT64,
                           SND_PCM_ACCESS_RW_NONINTERLEAVED,
                           1, rate, 0, 0 );
}

void Core::freePcm()
{
    if( NULL != mPcm )
        delete mPcm;

    mPcm = NULL;
}

bool Core::stepFirst()
{
}

bool Core::stepNext()
{
}
