/**
 * @file util/Misc.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "util/Misc.h"

using namespace cgt;
using namespace cgt::util;

/*************************************************************************/
/* cgt::util                                                             */
/*************************************************************************/
double util::normalize( double value, double period )
{
    int k = ( value + ::copysign( period / 2, value ) ) / period;
    return value -= k * period;
}
