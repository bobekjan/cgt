/**
 * @file stats/Periodic.inl
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* cgt::stats::Periodic                                                  */
/*************************************************************************/
template< typename S, typename R >
Periodic< S, R >::Periodic( Target* target, Sample period )
: Base( target ),
  mPeriod( period )
{
}

template< typename S, typename R >
void Periodic< S, R >::add( Sample sample )
{
    Base::add( util::normalizeAngle( sample, mPeriod ) );
}
