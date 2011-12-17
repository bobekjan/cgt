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

/// Names of notes.
extern const char* NOTE_NAMES[];
/// Number of notes per octave.
extern const int   NOTES_PER_OCTAVE;
/// Number of cents per note.
extern const int   CENTS_PER_NOTE;

/// Integer index of note A4.
extern const int    A4_INDEX;
/// Frequency of note A4.
extern const double A4_FREQ;

/**
 * @brief Normalizes angle to some given period.
 *
 * @param[in] angle  The angle to normalize.
 * @param[in] period The period of the angle.
 *
 * @return The normalized angle.
 */
double normalizeAngle( double angle, double period );

/**
 * @brief Generates a name for some given frequency.
 *
 * @param[in]  freq The frequency.
 * @param[out] name The name buffer.
 * @param[out] len  Length of the name buffer.
 */
void nameFreq( double freq, char* name, size_t len );

}} // cgt::util

#endif /* !__CGT__UTIL__MISC_H__INCL__ */
