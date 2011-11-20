/**
 * @file stats/Derivative.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __STATS__DERIVATIVE_H__INCL__
#define __STATS__DERIVATIVE_H__INCL__

#include "stats/IParent.h"

namespace stats
{
/**
 * @brief Computes derivative of samples.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class Derivative
: public IParent< S, R >
{
    /// Readability typedef of base.
    typedef IParent< S, R > Base;

public:
    /// Retain sample type from base.
    typedef typename Base::Sample Sample;
    /// Retain result type from base.
    typedef typename Base::Result Result;
    /// Retain child type from base.
    typedef typename Base::Child  Child;

    /**
     * @brief The primary constructor.
     *
     * @param[in] child The child counter.
     */
    Derivative( Child* child );
    /**
     * @brief The alternative contructor.
     *
     * Initializes the last sample value at contruction time.
     *
     * @param[in] child      The child counter.
     * @param[in] lastSample Value of the last sample.
     */
    Derivative( Child* child, Sample lastSample );

    /**
     * @brief Adds the sample for processing.
     */
    void add( Sample sample ) { ( this->*ADD_ROUTINES[ mState ] )( sample ); }
    /**
     * @brief Resets the derivative.
     */
    void reset();

protected:
    /**
     * @brief Describes state of the object.
     *
     * @author Bloody.Rabbit
     */
    enum State
    {
        STATE_INIT,   ///< The last sample value not initalized yet.
        STATE_RUNNING ///< The last sample value initalized, running.
    };

    /**
     * @brief Adds sample in the init state.
     *
     * Only initializes the last sample value.
     */
    void addInit( Sample sample );
    /**
     * @brief Adds sample in the running state.
     *
     * Computes the derivative.
     */
    void addRunning( Sample sample );

    /// The immediate state.
    State  mState;
    /// The last sample.
    Sample mLastSample;

    /// Jump table related to the state.
    static void ( Derivative::* ADD_ROUTINES[] )( Sample );
};

// Include the template code.
#include "stats/Derivative.inl"

} // stats

#endif /* !__STATS__DERIVATIVE_H__INCL__ */
