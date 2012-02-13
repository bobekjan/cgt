/**
 * @file stats/Maximum.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__STATS__MAXIMUM_H__INCL__
#define __CGT__STATS__MAXIMUM_H__INCL__

#include "stats/ICounter.h"

namespace cgt { namespace stats {

/**
 * @brief Captures maximum sample.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class Maximum
: public ICounter< S, R >
{
    /// Readability typedef of base.
    typedef ICounter< S, R > Base;

public:
    /// Retain sample type from base.
    typedef typename Base::Sample Sample;
    /// Retain result type from base.
    typedef typename Base::Result Result;

    /**
     * @brief Initializes the maximum counter.
     */
    Maximum();

    /**
     * @brief Checks if the counter is ready.
     */
    bool ready() const;
    /**
     * @brief Obtains the average of last mLimit samples.
     */
    Result result() const;

    /**
     * @brief Adds a sample for processing.
     */
    void add( Sample sample );
    /**
     * @brief Resets the counter.
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
        STATE_INIT,   ///< The maximum value not initalized yet.
        STATE_RUNNING ///< The maximum value initalized, running.
    };

    /**
     * @brief Adds sample in the init state.
     *
     * Only initializes the maximum sample value.
     */
    void addInit( Sample sample );
    /**
     * @brief Adds sample in the running state.
     *
     * Computes the maximum.
     */
    void addRunning( Sample sample );

    /// The maximum so far.
    Result mMax;
    /// Current state
    State  mState;

    /// Jump table related to the state.
    static void ( Maximum::* ADD_ROUTINES[] )( Sample );
};

// Include the template code.
#include "stats/Maximum.inl"

}} // cgt::stats

#endif /* !__CGT__STATS__MAXIMUM_H__INCL__ */
