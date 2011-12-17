/**
 * @file stats/IFilter.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__STATS__IFILTER_H__INCL__
#define __CGT__STATS__IFILTER_H__INCL__

#include "stats/ICounter.h"

namespace cgt { namespace stats {

/**
 * @brief A statistics counter filter.
 *
 * Does something with the value, then passes it
 * to another wrapped ICounter.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class IFilter
: public ICounter< S, R >
{
    /// Readability typedef of base.
    typedef ICounter< S, R > Base;

public:
    /// Retain sample type from base.
    typedef typename Base::Sample      Sample;
    /// Retain result type from base.
    typedef typename Base::Result      Result;
    /// Readability typedef of target.
    typedef ICounter< Sample, Result > Target;

    /**
     * @brief The primary constructor.
     *
     * @param[in] target The target counter.
     */
    IFilter( Target* target ) : mTarget( target ) {}
    /**
     * @brief Releases the target.
     */
    ~IFilter() { util::safeDelete( mTarget ); }

    /**
     * @brief Checks if the target is ready.
     */
    bool ready() const { return mTarget->ready(); }
    /**
     * @brief Obtains a result from the target.
     */
    Result result() const { return mTarget->result(); }

    /**
     * @brief Adds a sample to the target.
     */
    void add( Sample sample ) { return mTarget->add( sample ); }
    /**
     * @brief Resets the target.
     */
    void reset() { mTarget->reset(); }

protected:
    /// Target counter.
    Target* mTarget;
};

}} // cgt::stats

#endif /* !__CGT__STATS__IFILTER_H__INCL__ */
