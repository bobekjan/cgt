/**
 * @file stats/AverageRing.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __STATS__AVERAGE_RING_H__INCL__
#define __STATS__AVERAGE_RING_H__INCL__

#include "stats/ICounter.h"

namespace stats
{
/**
 * @brief Keeps a running average of last N samples.
 *
 * @todo Could probably be improved by using an actual ring buffer.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class AverageRing
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
     * @brief The primary constructor.
     *
     * @param[in] limit The limit of averaged samples.
     */
    AverageRing( unsigned int limit );

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
    /// A limit of samples.
    const unsigned int mLimit;

    /// A sum of last mLimit samples.
    Result               mSampleSum;
    /// A queue of last mLimit samples.
    std::queue< Sample > mLastSamples;
};

// Include the template code.
#include "stats/AverageRing.inl"

} // stats

#endif /* !__STATS__AVERAGE_RING_H__INCL__ */
