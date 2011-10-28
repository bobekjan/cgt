#!/usr/bin/env python
#
# Messing with "scipy" and like.
# Copyright (c) 2011 by Bloody.Rabbit
#

def normalize_angle( angle, period ):
    wrap = angle + period
    if numpy.abs( wrap ) < numpy.abs( angle ):
        return wrap

    wrap = angle - period
    if numpy.abs( wrap ) < numpy.abs( angle ):
        return wrap

    return angle

#-----------------------------------------

# MAX_LOW_CUTOFF = 1e-06
MAX_LOW_CUTOFF = 6e+06
MAX_BOUND_RATIO_DB = -2.0

def find_maxes( y ):
    maxesSingle = []
    maxesBound = []

    # Skip first element (magic)

    # Is strong enough?
    if MAX_LOW_CUTOFF <= y[ 1 ]:
        # Is local max?
        if y[ 1 ] > y[ 2 ]:
            # Is following neighbour strong enough?
            if MAX_BOUND_RATIO_DB <= 10 * numpy.log10( y[ 2 ] / y[ 1 ] ):
                # Bound frequency pair
                maxesBound.append( ( 1, 2 ) )
            else:
                # Single frequency
                maxesSingle.append( 1 )

    for f in range( 2, y.shape[ 0 ] - 1 ):
        # Is strong enough?
        if MAX_LOW_CUTOFF <= y[ f ]:
            # Is local max?
            if y[ f - 1 ] < y[ f ] and y[ f ] > y[ f + 1 ]:
                # Is following neighbour stronger than previous?
                if y[ f - 1 ] < y[ f + 1 ]:
                    # Is following neighbour strong enough?
                    if MAX_BOUND_RATIO_DB <= 10 * numpy.log10( y[ f + 1 ] / y[ f ] ):
                        # Bound frequency pair
                        maxesBound.append( ( f, f + 1 ) )
                    else:
                        # Single frequency
                        maxesSingle.append( f )
                else:
                    # Is previous neighbour strong enough?
                    if MAX_BOUND_RATIO_DB <= 10 * numpy.log10( y[ f - 1 ] / y[ f ] ):
                        # Bound frequency pair
                        maxesBound.append( ( f - 1, f ) )
                    else:
                        # Single frequency
                        maxesSingle.append( f )

    # Is strong enough?
    if MAX_LOW_CUTOFF <= y[ y.shape[ 0 ] - 1 ]:
        # Is local max?
        if y[ y.shape[ 0 ] - 2 ] < y[ y.shape[ 0 ] - 1 ]:
            # Is previous neighbour strong enough?
            if MAX_BOUND_RATIO_DB <= 10 * numpy.log10( y[ y.shape[ 0 ] - 2 ] / y[ y.shape[ 0 ] - 1 ] ):
                # Bound frequency pair
                maxesBound.append( ( y.shape[ 0 ] - 2, y.shape[ 0 ] - 1 ) )
            else:
                # Single frequency
                maxesSingle.append( y.shape[ 0 ] - 1 )

    return maxesSingle, maxesBound

#---------------------------------

class AngularHistory:
    def __init__( self, avBase, angle ):
        self.mAngle = angle

        self.mAvBase    = avBase
        self.mAvSum     = 0.0
        self.mAvSamples = 0

    def angularVelocity( self ):
        return self.mAvBase + self.mAvSum / self.mAvSamples

    def frequency( self ):
        return self.angularVelocity() / ( 2 * numpy.pi )

    def update( self, angle ):
        av = normalize_angle( angle - self.mAngle, 2 * numpy.pi )

        self.mAngle      = angle
        self.mAvSum     += av
        self.mAvSamples += 1

#---------------------------------

# Number of samples of the test
SAMPLES = 24

# Start freqency
FREQ_START = 2.5
# Count of freqency steps
FREQ_STEPS = 64 + 1
# End frequency
FREQ_END   = 3.0

def get_freq( i ):
    return FREQ_START + i * ( FREQ_END - FREQ_START ) / ( FREQ_STEPS - 1 )

#---------------------------------

def tmag( mag ):
    return 1.5**mag
    #return numpy.exp( mag )

def compute_mags( y ):
    z = numpy.empty( y.shape[ 0 ] / 2 + 1 )

    z[ 0 ] = numpy.abs( y[ 0 ] )

    for i in range( 1, y.shape[ 0 ] / 2 ):
        z[ i ] = numpy.sqrt( y[ 2 * i - 1 ]**2 + y[ 2 * i ]**2 )

    z[ -1 ] = numpy.abs( y[ -1 ] )

    return z

#-----------------------------------------

def print_fft( y ):
    # 1st header
    print "|     Step     |",
    for i in range( y.shape[ 1 ] / 2 + 1 ):
        #print "   %02d   |" % i,
        print "       %d        |" % i,
    print ""

    # 2nd header
    print "|             |",
    for i in range( y.shape[ 1] / 2 + 1 ):
        print "  cos     sin   |",
    print ""

    # Lines
    for i in range( y.shape[ 0 ] ):
        # Step
        print "| #%02d: %7.4f |" % ( i, get_freq( i ) ),

        #freqsum = magsum = 0.0

        # Offset
        off = y[ i ][ 0 ]
        #offmag = numpy.abs( off )

        #freqsum += 0 * tmag( offmag )
        #magsum += tmag( offmag )

        #print "%7.4f |" % offmag,
        print "------- %7.4f |" % off,

        # Middle frequencies
        for j in range( 1, y.shape[ 1 ]/2 ):
            # Variables
            cos  = y[ i ][ 2*j - 1 ]
            sin  = y[ i ][ 2*j ]
            #mag  = numpy.abs( cos ) + numpy.abs( sin )
            #mag  = numpy.sqrt( ( cos**2 ) + ( sin**2 ) )

            #freqsum += j * tmag( mag )
            #magsum += tmag( mag )

            # Print
            #print "%7.4f |" % mag,
            print "%7.4f" % cos,
            print "%7.4f |" % sin,

        # Nyquist frequency
        nyq = y[ i ][ y.shape[ 1 ] - 1 ]
        #nyqmag = numpy.abs( nyq )

        #freqsum += ( y.shape[ 1 ] / 2 ) * tmag( nyqmag )
        #magsum += tmag( nyqmag )

        #print "%7.4f |" % nyqmag,
        print "%7.4f ------- |" % nyq

        # Sum
        #print "%7.4f" % y[ i ].sum()
        #print "%7.4f" % ( freqsum / magsum - get_freq( i ) )
        #print "%7.4f %7.4f %7.4f" % ( freqsum, magsum, freqsum / magsum )

#---------------------------------

def render_fft( y ):
    # 3D plotting and visualisation
    import mayavi.mlab

    z = numpy.empty( ( y.shape[ 0 ], y.shape[ 1 ] / 2 + 1 ) )
    for i in range( y.shape[ 0 ] ):
        z[ i ] = compute_mags( y[ i ] )

    mayavi.mlab.barchart( z )
    mayavi.mlab.show()

        # freqsum = magsum = 0.0

        # # Offset
        # off    = y[ i ][ 0 ]
        # offmag = numpy.abs( off )

        # z[ i ][ 0 ] = offmag
        # freqsum    += 0 * tmag( offmag )
        # magsum     += tmag( offmag )

        # # Middle frequencies
        # for j in range( 1, y.shape[ 1 ]/2 ):
        #     cos = y[ i ][ 2*j - 1 ]
        #     sin = y[ i ][ 2*j ]
        #     #mag  = numpy.abs( cos ) + numpy.abs( sin )
        #     mag  = numpy.sqrt( ( cos**2 ) + ( sin**2 ) )

        #     z[ i ][ j ] = mag
        #     freqsum    += j * tmag( mag )
        #     magsum     += tmag( mag )

        # # Nyquist frequency
        # nyq = y[ i ][ y.shape[ 1 ] - 1 ]
        # nyqmag = numpy.abs( nyq )

        # z[ i ][ y.shape[ 1 ] / 2 ] = nyqmag
        # freqsum                   += ( y.shape[ 1 ] / 2 ) * tmag( nyqmag )
        # magsum                    += tmag( nyqmag )

        # # Stats
        # #z[ i ][ -1 ] = magsum
        # #z[ i ][ -1 ] = y[ i ].sum()
        # z[ i ][ -1 ]  = freqsum / magsum - get_freq( i )# + numpy.sin( 2 * numpy.pi * i / ( y.shape[ 0 ] - 1 ) )

#---------------------------------

# Math lib
import math
# numerical computing
import numpy
# FFT implementation
import scipy.fftpack
# WAVE utilities
import wave

# Our utilities
import notes

# mayavi.mlab.barchart(
#     [
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.000, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.125, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.250, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.375, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.500, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.625, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.750, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 2.875, RESOLUTION, endpoint = False ) ) ),
#         scipy.fftpack.rfft( numpy.cos( numpy.linspace( 0, 2 * numpy.pi * 3.000, RESOLUTION, endpoint = False ) ) )
#     ]
# )
# mayavi.mlab.show()

# grid = numpy.empty( ( FREQ_STEPS, SAMPLES ) )
# for i in range( grid.shape[ 0 ] ):
#     grid[ i ] = numpy.linspace( 0, 2 * numpy.pi * get_freq( i ), SAMPLES, endpoint = False )

# #x = numpy.exp(  0 ) * numpy.cos( 1 * grid ) \
# #  + numpy.exp(  0 ) * numpy.cos( 2 * grid ) \
# #  + numpy.exp(  0 ) * numpy.cos( 3 * grid ) \
# #  + numpy.exp(  0 ) * numpy.cos( 4 * grid ) \
# #  + numpy.exp(  0 ) * numpy.cos( 5 * grid )

# x = numpy.cos( grid )
# y = scipy.fftpack.rfft( x )

# print_fft( y )
# #render_fft( y )

# print ""

# #for i in range( y.shape[ 0 ] ):
# #    print "%7.4f:" % get_freq( i ), detect_freqs( y[ i ] )

SAMPLE_RATE = 48000
PERIOD      = 2
WINDOW_RATE = 20
WINDOW_SIZE = SAMPLE_RATE / WINDOW_RATE
# HARMONICS   = 6
# NOTE_FREQ  = 82.406889 # E2
# #NOTE_FREQ  = 440.000000 # A4
# #NOTE_FREQ  = 329.627557 # E4
# #NOTE_FREQ  = 2093.004522 # C7
# #NOTE_FREQ  = WINDOW_RATE * 8.0015625
# #NOTE_FREQ  = WINDOW_RATE * ( 4 - 0.0015625 )
# #NOTE_FREQ = 20.1017

# # Generate note freqency
# x = numpy.linspace( 0, 2 * numpy.pi * NOTE_FREQ * PERIOD, SAMPLE_RATE * PERIOD, endpoint = False )

# # Generate fundamental and harmonics
# y = numpy.zeros( ( SAMPLE_RATE * PERIOD ) )
# for i in range( 0, 1 + HARMONICS ):
#     y += numpy.exp( -i / 16.0 ) * numpy.cos( ( i + 1 ) * x + math.radians( 0 ) )

# import mayavi.mlab
# mayavi.mlab.barchart(  )
# mayavi.mlab.show()

WAV_FILENAME = "test.wav"
WAV_OFFSET   = 80000

wav_file = wave.open( WAV_FILENAME, "r" )
nchannels = wav_file.getnchannels()
sampwidth = wav_file.getsampwidth()

print "Filename: %s" % WAV_FILENAME
print "Channels: %d" % nchannels
print "Sample width: %d" % sampwidth
print "Sample frequency: %d" % wav_file.getframerate()
print "Sample count: %d" % wav_file.getnframes()
print "Compression: %s (%s)" % ( wav_file.getcompname(), wav_file.getcomptype() )
print ""

wav_file.setpos( WAV_OFFSET )
frames = wav_file.readframes( SAMPLE_RATE * PERIOD )

channels = []
for i in range( len( frames ) / ( nchannels * sampwidth ) ):
    for j in range( nchannels ):
        samp = 0

        for k in range( sampwidth ):
            samp |= ord( frames[ i * nchannels * sampwidth + j * nchannels + k ] ) << ( 8 * k )

        if len( channels ) <= j:
            channels.append( [ samp ] )
        else:
            channels[ j ].append( samp )
    
print "FFT of %d frames (offset %d) of first channel:" % ( SAMPLE_RATE * PERIOD, WAV_OFFSET )
y = channels[ 0 ]

# Run FFT
z = numpy.empty( ( WINDOW_RATE * PERIOD, WINDOW_SIZE ) )
for i in range( 0, z.shape[ 0 ] ):
    z[ i ] = scipy.fftpack.rfft( y[ (WINDOW_SIZE*i):(WINDOW_SIZE*(i+1)) ] )

angHist = {}
for i in range( z.shape[ 0 ] ):
    zm = compute_mags( z[ i ] )
    maxesSingle, maxesBound = find_maxes( zm )

    for f in maxesSingle:
        #if 0 == f:
        #    cos = 0.0
        #    sin = z[ i ][ 2 * f ]
        #    ang = math.asin( sin / WINDOW_SIZE )
        #elif SAMPLE_RATE / 2 == f:
        #    cos = z[ i ][ 2 * f - 1 ]
        #    sin = 0.0
        #    ang = math.acos( cos / WINDOW_SIZE )
        #else:
        cos     = z[ i ][ 2 * f - 1 ]
        sin     = z[ i ][ 2 * f ]
        ang     = math.atan2( sin, cos )
        #ang     = math.atan( sin / cos )

        if f in angHist:
            ah = angHist[ f ]
            ah.update( ang )

            freq = WINDOW_RATE * ah.frequency()
            octave, note, cents = notes.nameFreq( freq )
            name = notes.noteName( octave, note, cents )

            print "     %4d: freq=%10.4f (%s)" \
            % ( f, freq, name )
        else:
            angHist[ f ] = AngularHistory( 2 * numpy.pi * f, ang )

            print "     %4d: freq=----------" \
            % ( f )

    for f1, f2 in maxesBound:
        print "%4d %4d:" % ( f1, f2 ),

        # f1 -------------------------------------
        ang = math.atan2( z[ i ][ 2 * f1 ],
                          z[ i ][ 2 * f1 - 1 ] )

        if f1 in angHist:
            ah = angHist[ f1 ]

            ah.update( ang )
            f1x = ah.frequency()
        else:
            angHist[ f1 ] = AngularHistory( 2 * numpy.pi * f1, ang )
            f1x = None

        # f2 -------------------------------------
        ang = math.atan2( z[ i ][ 2 * f2 ],
                          z[ i ][ 2 * f2 - 1 ] )

        if f2 in angHist:
            ah = angHist[ f2 ]

            ah.update( ang )
            f2x = ah.frequency()
        else:
            angHist[ f2 ] = AngularHistory( 2 * numpy.pi * f2, ang )
            f2x = None

        # f --------------------------------------
        if f1x == None:
            if f2x == None:
                freq = None
            else:
                freq = f2x
        else:
            if f2x == None:
                freq = f1x
            else:
                if f1 <= f1x and f1x <= f2:
                    if f1 <= f2x and f2x <= f2:
                        #print "!!! ALIASING !!!"
                        freq = None
                    else:
                        freq = f1x
                else:
                    if f1 <= f2x and f2x <= f2:
                        freq = f2x
                    else:
                        #print "!!! ALIASING !!!"
                        freq = None

        # print ----------------------------------
        if freq == None:
            print "freq=----------"
        else:
            freq *= WINDOW_RATE
            octave, note, cents = notes.nameFreq( freq )
            name = notes.noteName( octave, note, cents )

            print "freq=%10.4f (%s)" % ( freq, name )

    print "-------"
