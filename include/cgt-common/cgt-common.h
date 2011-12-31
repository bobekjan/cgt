/**
 * @file cgt-common.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT_COMMON_H__INCL__
#define __CGT_COMMON_H__INCL__

/*************************************************************************/
/* Configuration definitions                                             */
/*************************************************************************/
// Include config.h if we have any
#ifdef HAVE_CONFIG_H
#   include "config.h"
#endif /* HAVE_CONFIG_H */

// "Explicitly request" fixed-width integer format macros
#define __STDC_FORMAT_MACROS 1

/*************************************************************************/
/* Standard includes                                                     */
/*************************************************************************/
// C standard library
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>

// C++ standard library
#include <queue>
#include <vector>

/*************************************************************************/
/* Platform includes                                                     */
/*************************************************************************/
// inttypes.h
#ifdef HAVE_INTTYPES_H
#   include <inttypes.h>
#endif /* HAVE_INTTYPES_H */

/*************************************************************************/
/* Dependencies' includes                                                */
/*************************************************************************/
// ALSA library
#include <asoundlib.h>

// fftw3 library
#include <fftw3.h>

/*************************************************************************/
/* Our includes                                                          */
/*************************************************************************/
// Platform compatibility code
#include "cgt-compat.h"

// Safe memory management utilities
#include "util/SafeMem.h"

#endif /* !__CGT_COMMON_H__INCL__ */
