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
    void start();
    void add( double freq );
    void end();

#ifdef CGT_DEBUG_ANALYSE_HARMONICS
    unsigned int getHarmonic( double freq );
    void clearHarmonic();
#endif /* CGT_DEBUG_ANALYSE_HARMONICS */

protected:
#ifdef CGT_DEBUG_ANALYSE_HARMONICS
    /// A vector of fundamentals.
    std::vector< double > mFundamentals;
#endif /* CGT_DEBUG_ANALYSE_HARMONICS */

    /// A buffer for note name.
    char mName[ 0x20 ];
};

}} // cgt::curses

#endif /* !__CGT__CURSES__OBSERVER_H__INCL__ */
