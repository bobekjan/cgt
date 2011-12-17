/**
 * @file stats/Periodic.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__STATS__PERIODIC_H__INCL__
#define __CGT__STATS__PERIODIC_H__INCL__

#include "stats/IFilter.h"
#include "util/Misc.h"

namespace cgt { namespace stats {

/**
 * @brief A counter to keep the samples in a certain period.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class Periodic
: public IFilter< S, R >
{
    /// Readability typedef of base.
    typedef IFilter< S, R > Base;

public:
    /// Retain sample type from base.
    typedef typename Base::Sample Sample;
    /// Retain result type from base.
    typedef typename Base::Result Result;
    /// Retain target type from base.
    typedef typename Base::Target  Target;

    /**
     * @brief The primary constructor.
     *
     * @param[in] target The target counter.
     * @param[in] period The period of the samples.
     */
    Periodic( Target* target, Sample period );

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

}} // cgt::stats

#endif /* !__CGT__STATS__PERIODIC_H__INCL__ */
