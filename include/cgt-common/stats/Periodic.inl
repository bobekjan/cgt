/**
 * @file stats/Periodic.inl
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* stats::Periodic                                                       */
/*************************************************************************/
template< typename S, typename R >
Periodic< S, R >::Periodic( Child* child, Sample period )
: Base( child ),
  mPeriod( period )
{
}

template< typename S, typename R >
void Periodic< S, R >::add( Sample sample )
{
    Base::add( util::normalizeAngle( sample, mPeriod ) );
}
