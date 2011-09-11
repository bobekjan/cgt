#!/usr/bin/env python
#
# Print notes with their physical frequencies.
# Copyright (c) 2011 by Bloody.Rabbit
#

import math

NOTE_NAMES = [ "C",  "C#", "D",  "Eb",
               "E",  "F",  "F#", "G",
               "G#", "A",  "Bb", "B" ]

NOTES_PER_OCTAVE = 12
NOTES_PER_CENT   = 0.01

A4_INDEX = 4 * NOTES_PER_OCTAVE + 9
A4_FREQ = 440.0

def noteName( octave, note, cents ):
    return "%s%d.%+05.1f" % ( NOTE_NAMES[ note ], octave, cents )

def nameFreq( freq ):
    try:
        cents, note = math.modf( A4_INDEX + NOTES_PER_OCTAVE * math.log( freq / A4_FREQ, 2 ) )
        note        = int( note )
        cents       = cents / NOTES_PER_CENT

        # Wrap cents
        if 1 / ( 2 * NOTES_PER_CENT ) < cents:
            note  += 1
            cents -= 1 / NOTES_PER_CENT

        # Wrap notes
        octave = note / NOTES_PER_OCTAVE
        note -= octave * NOTES_PER_OCTAVE

        return octave, note, cents
    except ValueError, e:
        print "Cannot determine for freqency %10.4f" % freq

def noteFreq( octave, note, cents ):
    index = octave * NOTES_PER_OCTAVE + note + cents * NOTES_PER_CENT
    return A4_FREQ * 2.0**( float( index - A4_INDEX ) / NOTES_PER_OCTAVE )

"""
print "|   Note   |",
for octave in range( 0, 10 ):
    print "      %d      |" % octave,
print ""

for note in range( 0, 12 ):
    for cents in range( -500, 500 ):
        print "| %s |" % noteName( note, 0.1 * cents),
        for octave in range( 0, 10 ):
            print "%12f |" % noteFreq( octave, note, 0.1 * cents ),

        print ""
"""
"""
FREQ = 440

print FREQ

octave, note, cents = nameFreq( FREQ )
print noteName( octave, note, cents )

print noteFreq( octave, note, cents )
"""
