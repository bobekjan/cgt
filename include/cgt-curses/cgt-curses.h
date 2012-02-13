/**
 * @file cgt-curses.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT_CURSES_H__INCL__
#define __CGT_CURSES_H__INCL__

/*************************************************************************/
/* cgt-common                                                            */
/*************************************************************************/
#include "cgt-common.h"

#include "alsa/Pcm.h"
#include "config/ArgvParser.h"
#include "config/ConfigMgr.h"
#include "core/FftAnalyser.h"
#include "stats/Maximum.h"
#include "util/Harmonics.h"
#include "util/Misc.h"

/*************************************************************************/
/* cgt-curses                                                            */
/*************************************************************************/
#include <curses.h>

// Color pair for fundamentals
#define PAIR_FUNDAMENTAL 1
// Color pair for config
#define PAIR_CONFIG      2
// Color pair for magnitude bar
#define PAIR_MAGBAR      3
// Color pair for tuner bar, good
#define PAIR_TUNER_GOOD  4
// Color pair for tuner bar, bad
#define PAIR_TUNER_BAD   5
// Color pair for tuner bar arrows
#define PAIR_TUNER_ARROW 6

using namespace cgt;

#endif /* !__CGT_CURSES_H__INCL__ */
