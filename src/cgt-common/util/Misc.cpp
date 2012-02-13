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
const char* util::NOTE_NAMES[] =
{
    "C",  // NOTE_C
    "C#", // NOTE_C_SHARP
    "D",  // NOTE_D
    "Eb", // NOTE_E_FLAT
    "E",  // NOTE_E
    "F",  // NOTE_F
    "F#", // NOTE_F_SHARP
    "G",  // NOTE_G
    "G#", // NOTE_G_SHARP
    "A",  // NOTE_A
    "Bb", // NOTE_B_FLAT
    "B"   // NOTE_B
};

const int util::NOTES_PER_OCTAVE = 12;
const int util::CENTS_PER_NOTE   = 100;

const int    util::A4_INDEX = NOTE_A + 4 * NOTES_PER_OCTAVE;
const double util::A4_FREQ  = 440.0;

double util::normalize( double value, double period )
{
    int k = ( value + ::copysign( period / 2, value ) ) / period;
    return value -= k * period;
}

double util::noteFreq( Note note, int octave, double cents )
{
    // Calculate index of the note
    const double index = octave * NOTES_PER_OCTAVE + note + cents / CENTS_PER_NOTE;

    // Compute the frequency
    return A4_FREQ * ::pow( 2, double( index - A4_INDEX ) / NOTES_PER_OCTAVE );
}

Note util::noteName( double freq, int& octave, double& cents )
{
    // Calculate index of the note
    double index  = A4_INDEX + NOTES_PER_OCTAVE * ::log2( freq / A4_FREQ );

    // Split note/cents
    cents  = CENTS_PER_NOTE * ::modf( index, &index );
    octave = 0;

    int note = index;
    int k    = 0;

    // Wrap cents
    k = ( cents + ::copysign( CENTS_PER_NOTE / 2, cents ) ) / CENTS_PER_NOTE;

    note  += k;
    cents -= k * CENTS_PER_NOTE;

    // Wrap notes
    k = ::floor( (double)note / NOTES_PER_OCTAVE );

    octave += k;
    note   -= k * NOTES_PER_OCTAVE;

    // Return casted note
    return static_cast< Note>( note );
}

void util::noteStr( Note note, int octave, double cents,
                    char* name, size_t len )
{
    // Print the name
    ::snprintf( name, len, "%s%d.%+05.1f",
                NOTE_NAMES[ note ], octave, cents );
}
