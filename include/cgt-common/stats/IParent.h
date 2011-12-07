/**
 * @file stats/IParent.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __STATS__IPARENT_H__INCL__
#define __STATS__IPARENT_H__INCL__

#include "stats/ICounter.h"

namespace stats
{
/**
 * @brief A statistics counter parent.
 *
 * Acts like a filter, passes values to a wrapped child.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class IParent
: public ICounter< S, R >
{
    /// Readability typedef of base.
    typedef ICounter< S, R > Base;

public:
    /// Retain sample type from base.
    typedef typename Base::Sample      Sample;
    /// Retain result type from base.
    typedef typename Base::Result      Result;
    /// Readability typedef of child.
    typedef ICounter< Sample, Result > Child;

    /**
     * @brief The primary constructor.
     *
     * @param[in] child The child counter.
     */
    IParent( Child* child ) : mChild( child ) {}
    /**
     * @brief Releases the child.
     */
    ~IParent() { util::safeDelete( mChild ); }

    /**
     * @brief Checks if the child is ready.
     */
    bool ready() const { return mChild->ready(); }
    /**
     * @brief Obtains a result from the child.
     */
    Result result() const { return mChild->result(); }

    /**
     * @brief Adds a sample to the child.
     */
    void add( Sample sample ) { return mChild->add( sample ); }
    /**
     * @brief Resets the child.
     */
    void reset() { mChild->reset(); }

protected:
    /// Child counter.
    Child* mChild;
};

} // stats

#endif /* !__STATS__IPARENT_H__INCL__ */
