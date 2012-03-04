/**
 * @file util/Misc.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__UTIL__MISC_H__INCL__
#define __CGT__UTIL__MISC_H__INCL__

namespace cgt { namespace util {

/**
 * @brief Normalizes a value to some given period.
 *
 * The returned value is guaranteed to be from
 * the period of [-period/2; period/2].
 *
 * @param[in] value  The value to normalize.
 * @param[in] period The period of the value.
 *
 * @return The normalized value.
 */
double normalize( double value, double period );

}} // cgt::util

#endif /* !__CGT__UTIL__MISC_H__INCL__ */
