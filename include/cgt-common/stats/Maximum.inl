/**
 * @file stats/Maximum.inl
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* cgt::stats::Maximum                                                   */
/*************************************************************************/
template< typename S, typename R >
void ( Maximum< S, R >::* Maximum< S, R >::ADD_ROUTINES[] )( Sample ) =
{
    &Maximum::addInit,   // STATE_INIT
    &Maximum::addRunning // STATE_RUNNING
};

template< typename S, typename R >
Maximum< S, R >::Maximum()
: mMax( 0 ),
  mState( STATE_INIT )
{
}

template< typename S, typename R >
bool Maximum< S, R >::ready() const
{
    // Check if we are ready.
    return STATE_RUNNING == mState;
}

template< typename S, typename R >
typename Maximum< S, R >::Result Maximum< S, R >::result() const
{
    // Just return what we have so far
    return mMax;
}

template< typename S, typename R >
void Maximum< S, R >::add( Sample sample )
{
    // Jump using the state table.
    ( this->*ADD_ROUTINES[ mState ] )( sample );
}

template< typename S, typename R >
void Maximum< S, R >::reset()
{
    // Reset the maximum counter.
    mMax   = 0;
    mState = STATE_INIT;
}

template< typename S, typename R >
void Maximum< S, R >::addInit( Sample sample )
{
    // Store the first value unconditionally.
    mMax = sample;

    // Change state to running.
    mState = STATE_RUNNING;
}

template< typename S, typename R >
void Maximum< S, R >::addRunning( Sample sample )
{
    // Store the bigger of the two.
    mMax = std::max( mMax, sample );
}
