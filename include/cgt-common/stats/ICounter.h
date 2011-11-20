/**
 * @file stats/ICounter.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __STATS__ICOUNTER_H__INCL__
#define __STATS__ICOUNTER_H__INCL__

/**
 * @brief Utilities related to statistics.
 *
 * @author Bloody.Rabbit
 */
namespace stats
{
/**
 * @brief An interface of a generic statistics counter.
 *
 * @author Bloody.Rabbit
 */
template< typename S, typename R >
class ICounter
{
public:
    /// Type of processed samples.
    typedef S Sample;
    /// Type of result value.
    typedef R Result;

    /**
     * @brief Checks if the counter is ready.
     *
     * Basically means that calling result() will yield
     * a reasonable value.
     *
     * @retval true  The counter is ready.
     * @retval false The counter is not ready.
     */
    virtual bool ready() const = 0;
    /**
     * @brief Obtains a statistical result.
     *
     * @return The result.
     */
    virtual Result result() const = 0;

    /**
     * @brief Adds a sample for processing.
     *
     * @param[in] sample The sample.
     */
    virtual void add( Sample sample ) = 0;
    /**
     * @brief Resets the statistics.
     */
    virtual void reset() = 0;
};

} // stats

#endif /* !__STATS__ICOUNTER_H__INCL__ */
