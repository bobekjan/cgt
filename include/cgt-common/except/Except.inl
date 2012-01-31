/**
 * @file except/Except.inl
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* cgt::except::GracefulExit                                             */
/*************************************************************************/
inline GracefulExit::GracefulExit( const std::string& what_arg )
: LogicError( what_arg )
{
}
