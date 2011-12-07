/**
 * @file stats/Periodic.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __STATS__PERIODIC_H__INCL__
#define __STATS__PERIODIC_H__INCL__

#include "stats/IParent.h"
#include "util/Misc.h"

namespace stats
{
/**
 * @brief A counter to keep the samples in a certain period.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class Periodic
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
     * @param[in] child  The child counter.
     * @param[in] period The period of the samples.
     */
    Periodic( Child* child, Sample period );

    /**
     * @brief Adds a sample for processing.
     */
    void add( Sample sample );

protected:
    /// The period.
    const Sample mPeriod;
};

// Include the template code.
#include "stats/Periodic.inl"

} // stats

#endif /* !__STATS__PERIODIC_H__INCL__ */