/**
 * @file util/Harmonics.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__UTIL__HARMONICS_H__INCL__
#define __CGT__UTIL__HARMONICS_H__INCL__

namespace cgt { namespace util {

/**
 * @brief A helper class for analyzing harmonics.
 *
 * @author Bloody.Rabbit
 */
class Harmonics
{
public:
    /**
     * @brief Initializes the harmonics analyser.
     *
     * @param[in] tol The harmonic tolerance.
     */
    Harmonics( double tol );

    /**
     * @brief Obtains the harmonic tolerance.
     */
    double tolerance() const { return mTolerance; }
    /**
     * @brief Sets the harmonic tolerance.
     *
     * @param[in] tol The new value.
     */
    void setTolerance( double tol ) { mTolerance = tol; }

    /**
     * @brief Obtains harmonic index of a frequency.
     *
     * @param[in] freq The frequency.
     *
     * @return The harmonic index.
     */
    unsigned int get( double freq );
    /**
     * @brief Clears all intermediate data.
     */
    void clear();

protected:
    /// A vector of fundamentals.
    std::vector< double > mFundamentals;
    /// A harmonic tolerance.
    double mTolerance;
};

}} // cgt::util


#endif /* !__CGT__UTIL__HARMONICS_H__INCL__ */
