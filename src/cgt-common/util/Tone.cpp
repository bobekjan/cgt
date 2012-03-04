/**
 * @file util/Tone.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "util/Tone.h"

using namespace cgt;
using namespace cgt::util;

/*************************************************************************/
/* cgt::util::Tone                                                       */
/*************************************************************************/
const char* Tone::NOTE_NAMES[] =
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

const int Tone::NOTES_PER_OCTAVE = 12;
const int Tone::CENTS_PER_NOTE   = 100;

const int    Tone::A4_INDEX = NOTE_A + 4 * NOTES_PER_OCTAVE;
const double Tone::A4_FREQ  = 440.0;

Tone::Tone( double freq )
: mFrequency( freq )
{
    // Calculate index of the note
    double index  = A4_INDEX + NOTES_PER_OCTAVE * ::log2( freq / A4_FREQ );

    // Split note/cents
    mCents  = CENTS_PER_NOTE * ::modf( index, &index );
    mOctave = 0;

    int note = index;
    int k    = 0;

    // Wrap cents
    k = ( mCents + ::copysign( CENTS_PER_NOTE / 2, mCents ) ) / CENTS_PER_NOTE;

    note   += k;
    mCents -= k * CENTS_PER_NOTE;

    // Wrap notes
    k = ::floor( (double)note / NOTES_PER_OCTAVE );

    mOctave += k;
    note    -= k * NOTES_PER_OCTAVE;

    // Save casted note
    mNote = static_cast< Note>( note );
}

Tone::Tone( Note note, double cents, int octave )
: mNote( note ),
  mCents( cents ),
  mOctave( octave )
{
    // Calculate index of the note
    const double index = octave * NOTES_PER_OCTAVE + note + cents / CENTS_PER_NOTE;

    // Compute the frequency
    mFrequency = A4_FREQ * ::pow( 2, double( index - A4_INDEX ) / NOTES_PER_OCTAVE );
}

void Tone::getName( char* name, size_t len ) const
{
    // Print the name
    ::snprintf( name, len, "%s%d.%+05.1f",
                NOTE_NAMES[ note() ], octave(), cents() );
}
