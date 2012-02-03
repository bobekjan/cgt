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
#include "curses/NoteList.h"

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
     * @param[in] row    Row number of the top left corner.
     * @param[in] col    Column number of the top left corner.
     * @param[in] width  Width of the screen.
     * @param[in] height Height of the screen.
     */
    Screen( int row, int col, int width, int height );
    /**
     * @brief Deinitializes the observer.
     */
    ~Screen();

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
    /// Screen parameters.
    int mWidth, mHeight;

    /// Harmonics analyser.
    util::Harmonics mHarmonics;
    /// Configuration list.
    ConfigList      mConfig;
    /// Note list.
    NoteList        mNotes;
};

}} // cgt::curses

#endif /* !__CGT__CURSES__SCREEN_H__INCL__ */
