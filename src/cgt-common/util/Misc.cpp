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

using namespace util;

/*************************************************************************/
/* util                                                                  */
/*************************************************************************/
const char* util::NOTE_NAMES[] =
{
    "C",  "C#", "D",  "Eb",
    "E",  "F",  "F#", "G",
    "G#", "A",  "Bb", "B"
};

const int util::NOTES_PER_OCTAVE = 12;
const int util::CENTS_PER_NOTE   = 100;

const int    util::A4_INDEX = 4 * NOTES_PER_OCTAVE + 9;
const double util::A4_FREQ  = 440.0;

double util::normalizeAngle( double angle, double period )
{
    int k = ( angle + ::copysign( period / 2, angle ) ) / period;
    return angle -= k * period;
}

void util::nameFreq( double freq, char* name, size_t len )
{
    double index  = A4_INDEX + NOTES_PER_OCTAVE * ::log2( freq / A4_FREQ );
    double cents  = CENTS_PER_NOTE * ::modf( index, &index );

    int note   = index;
    int octave = 0;
    int k      = 0;

    // Wrap cents
    k = ( cents + ::copysign( CENTS_PER_NOTE / 2, cents ) ) / CENTS_PER_NOTE;

    note  += k;
    cents -= k * CENTS_PER_NOTE;

    // Wrap notes
    k = ::floor( (double)note / NOTES_PER_OCTAVE );

    octave += k;
    note   -= k * NOTES_PER_OCTAVE;

    // Print the name
    ::snprintf( name, len, "%s%d.%+05.1lf",
                NOTE_NAMES[ note ], octave, cents );
}
