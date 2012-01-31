/**
 * @file except/Except.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__EXCEPT__EXCEPT_H__INCL__
#define __CGT__EXCEPT__EXCEPT_H__INCL__

namespace cgt { namespace except {

// Rebind std::exception.
typedef std::exception Exception;

// Rebind std::logic_error.
typedef std::logic_error      LogicError;
// Rebind std::domain_error.
typedef std::domain_error     DomainError;
// Rebind std::invalid_argument.
typedef std::invalid_argument InvalidArgument;
// Rebind std::length_error.
typedef std::length_error     LengthError;
// Rebind std::out_of_range.
typedef std::out_of_range     OutOfRange;

// Rebind std::runtime_error.
typedef std::runtime_error   RuntimeError;
// Rebind std::range_error.
typedef std::range_error     RangeError;
// Rebind std::overflow_error.
typedef std::overflow_error  OverflowError;
// Rebind std::underflow_error.
typedef std::underflow_error UnderflowError;

/**
 * @brief A graceful-exit exception.
 *
 * Thrown when the program should unexpectedly,
 * but gracefully exit.
 *
 * Examples of usage include graceful termination
 * after printing help when parsing argv options.
 *
 * @author Bloody.Rabbit
 */
class GracefulExit
: public LogicError
{
public:
    /**
     * @brief Initializes the exception with an error message.
     *
     * @param[in] what_arg A description message.
     */
    explicit GracefulExit( const std::string& what_arg );
};

// Include inlined code.
#include "except/Except.inl"

}} // cgt::except

#endif /* !__CGT__EXCEPT__EXCEPT_H__INCL__ */
