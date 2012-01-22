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
 * @brief Enumeration of notes.
 *
 * @author Bloody.Rabbit
 */
enum Note
{
    NOTE_C,
    NOTE_C_SHARP,
    NOTE_D,
    NOTE_E_FLAT,
    NOTE_E,
    NOTE_F,
    NOTE_F_SHARP,
    NOTE_G,
    NOTE_G_SHARP,
    NOTE_A,
    NOTE_B_FLAT,
    NOTE_B
};

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

/**
 * @brief Generates a name for some given frequency.
 *
 * @param[in]  freq   The frequency.
 * @param[out] octave Output variable for octave.
 * @param[out] cents  Output variable for cents.
 *
 * @return The note name.
 */
Note noteName( double freq, int& octave, double& cents );
/**
 * @brief Generates a string for a given note.
 *
 * @param[in]  note   The note.
 * @param[in]  octave Octave of the note.
 * @param[in]  cents  Cents of the note.
 * @param[out] name   Where to print the string.
 * @param[out] len    Length of the name buffer.
 */
void noteStr( Note note, int octave, double cents,
              char* name, size_t len );

}} // cgt::util

#endif /* !__CGT__UTIL__MISC_H__INCL__ */
