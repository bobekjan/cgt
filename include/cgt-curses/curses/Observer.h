/**
 * @file curses/Observer.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CURSES__OBSERVER_H__INCL__
#define __CGT__CURSES__OBSERVER_H__INCL__

namespace cgt { namespace curses {

/**
 * @brief An observer based on curses.
 *
 * @author Bloody.Rabbit
 */
class Observer
: public core::Analyser::IObserver
{
public:
    /**
     * @brief Initializes the observer.
     *
     * @param[in] harmTol The harmonic tolerance.
     */
    Observer( double harmTol );
    /**
     * @brief Deinitializes the observer.
     */
    ~Observer();

    /**
     * @brief Obtains the harmonic tolerance.
     */
    double harmonicTolerance() const { return mHarmonicTolerance; }
    /**
     * @brief Sets the harmonic tolerance.
     *
     * @param[in] harmTol The new value.
     */
    void setHarmonicTolerance( double harmTol ) { mHarmonicTolerance = harmTol; }

    /**
     * @brief Starts analysis frame.
     */
    void start();
    /**
     * @brief Adds a frequency within analysis frame.
     */
    void add( double freq );
    /**
     * @brief Ends analysis frame.
     */
    void end();

protected:
    /**
     * @brief Obtains harmonic index for a frequency.
     *
     * @param[in] freq The frequency in question.
     *
     * @return The harmonic index.
     */
    unsigned int getHarmonic( double freq );

    /**
     * @brief Prints config parameters.
     *
     * @param[in] line  Line at which to print.
     * @param[in] title Title of the parameter.
     * @param[in] value Value of the parameter.
     */
    void printConfig( int line, const char* title, const char* value );

    /// A vector of fundamentals.
    std::vector< double > mFundamentals;
    /// A harmonic tolerance.
    double mHarmonicTolerance;

    /// A buffer for note name.
    char mName[ 0x20 ];
    /// Screen parameters.
    int mWidth, mHeight;
};

}} // cgt::curses

#endif /* !__CGT__CURSES__OBSERVER_H__INCL__ */
