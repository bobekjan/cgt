/**
 * @file stats/AverageRing.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* cgt::stats::AverageRing                                               */
/*************************************************************************/
template< typename S, typename R >
AverageRing< S, R >::AverageRing( unsigned int limit )
: mLimit( limit ),
  mSampleSum( 0 )
{
}

template< typename S, typename R >
bool AverageRing< S, R >::ready() const
{
    return 0 < mLastSamples.size();
}

template< typename S, typename R >
typename AverageRing< S, R >::Result AverageRing< S, R >::result() const
{
    return mSampleSum / mLastSamples.size();
}

template< typename S, typename R >
void AverageRing< S, R >::add( Sample sample )
{
    // Update the sample sum and the sample queue.
    mSampleSum += sample;
    mLastSamples.push( sample );

    // If the queue has grown over limit, drop oldest sample.
    if( mLimit < mLastSamples.size() )
    {
        mSampleSum -= mLastSamples.front();
        mLastSamples.pop();
    }
}

template< typename S, typename R >
void AverageRing< S, R >::reset()
{
    // Zero the sum.
    mSampleSum = 0;

    // Empty the queue.
    while( 0 < mLastSamples.size() )
        mLastSamples.pop();
}
