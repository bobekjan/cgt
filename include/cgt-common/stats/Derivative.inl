/**
 * @file stats/Derivative.inl
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* stats::Derivative                                                     */
/*************************************************************************/
template< typename S, typename R >
void ( Derivative< S, R >::* Derivative< S, R >::ADD_ROUTINES[] )( Sample ) =
{
    &Derivative::addInit,   // STATE_INIT
    &Derivative::addRunning // STATE_RUNNING
};

template< typename S, typename R >
Derivative< S, R >::Derivative( Target* target )
: Base( target ),
  mState( STATE_INIT )
{
}

template< typename S, typename R >
Derivative< S, R >::Derivative( Target* target, Sample lastSample )
: Base( target ),
  mState( STATE_RUNNING ),
  mLastSample( lastSample )
{
}

template< typename S, typename R >
void Derivative< S, R >::reset()
{
    // Reset the base.
    Base::reset();

    // Revert state back to init.
    mState = STATE_INIT;
}

template< typename S, typename R >
void Derivative< S, R >::addInit( Sample sample )
{
    // Initialize the last sample value.
    mLastSample = sample;

    // Switch state to running.
    mState = STATE_RUNNING;
}

template< typename S, typename R >
void Derivative< S, R >::addRunning( Sample sample )
{
    // Pass the derivative to target.
    Base::add( sample - mLastSample );

    // Update the last sample value.
    mLastSample = sample;
}
