/**
 * @file util/Tone.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__UTIL__TONE_H__INCL__
#define __CGT__UTIL__TONE_H__INCL__

namespace cgt { namespace util {

/**
 * @brief Utility class for dealing with tones/frequencies.
 *
 * @author Bloody.Rabbit
 */
class Tone
{
public:
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
    static const char* NOTE_NAMES[];
    /// Number of notes per octave.
    static const int   NOTES_PER_OCTAVE;
    /// Number of cents per note.
    static const int   CENTS_PER_NOTE;

    /// Integer index of note A4.
    static const int    A4_INDEX;
    /// Frequency of note A4.
    static const double A4_FREQ;

    /**
     * @brief Creates a tone based on its frequency.
     *
     * @param[in] freq The frequency of the tone.
     */
    Tone( double freq );
    /**
     * @brief Creates a tone based on its musical properties.
     *
     * @param[in] note   Base note of the tone.
     * @param[in] cents  Musical cents of the tone.
     * @param[in] octave Octave of the tone.
     */
    Tone( Note note, double cents, int octave );

    /**
     * @brief Obtains frequency of the tone.
     *
     * @return The frequency.
     */
    double frequency() const { return mFrequency; }

    /**
     * @brief Obtains base note of the tone.
     *
     * @return The note.
     */
    Note note() const { return mNote; }
    /**
     * @brief Obtains musical cents of the tone.
     *
     * @return Cents of the tone.
     */
    double cents() const { return mCents; }
    /**
     * @brief Obtains octave of the tone.
     *
     * @return Octave of the tone.
     */
    int octave() const { return mOctave; }

    /**
     * @brief Obtains name of the tone.
     *
     * @param[out] name The name buffer.
     * @param[out] len  Length of the name buffer.
     */
    void getName( char* name, size_t len ) const;

protected:
    // Frequency of the tone.
    double mFrequency;

    // Base of the tone.
    Note   mNote;
    // Musical cents of the tone.
    double mCents;
    // Octave of the tone.
    int    mOctave;
};

}} // cgt::util

#endif /* !__CGT__UTIL__TONE_H__INCL__ */
