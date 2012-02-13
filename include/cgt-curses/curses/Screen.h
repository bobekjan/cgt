/**
 * @file curses/Screen.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CURSES__SCREEN_H__INCL__
#define __CGT__CURSES__SCREEN_H__INCL__

#include "curses/ConfigList.h"
#include "curses/MagnitudeBar.h"
#include "curses/NoteList.h"
#include "curses/TunerBar.h"

namespace cgt { namespace curses {

/**
 * @brief An observer based on curses.
 *
 * @author Bloody.Rabbit
 */
class Screen
: public core::Analyser::IObserver
{
public:
    /**
     * @brief Initializes the observer.
     *
     * @param[in] xpos   Position in X-axis.
     * @param[in] ypos   Position in Y-axis.
     * @param[in] width  Size in X-axis.
     * @param[in] height Size in Y-axis.
     */
    Screen( int xpos, int ypos, int width, int height );

    /**
     * @brief Starts analysis frame.
     */
    void start();
    /**
     * @brief Adds a frequency within analysis frame.
     */
    void add( double freq, double mag );
    /**
     * @brief Ends analysis frame.
     */
    void end();

protected:
    /// Harmonics analyser.
    util::Harmonics mHarmonics;

    /// Configuration list.
    ConfigList   mConfig;
    /// Magnitude bar.
    MagnitudeBar mMagBar;
    /// Note list.
    NoteList     mNotes;
    /// Tuner bar.
    TunerBar     mTuner;
};

}} // cgt::curses

#endif /* !__CGT__CURSES__SCREEN_H__INCL__ */
