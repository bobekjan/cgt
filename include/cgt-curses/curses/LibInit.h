/**
 * @file curses/LibInit.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CURSES__LIB_INIT_H__INCL__
#define __CGT__CURSES__LIB_INIT_H__INCL__

namespace cgt { namespace curses {

/**
 * @brief Curses initialization class.
 *
 * @author Bloody.Rabbit
 */
class LibInit
{
public:
    /**
     * @brief Initializes the curses library.
     *
     * Implemented by <code>initscr</code>.
     */
    LibInit() { ::initscr(); }
    /**
     * @brief Deinitializes the curses library.
     *
     * Implemented by <code>endwin</code>.
     */
    ~LibInit() { ::endwin(); }

    /**
     * @brief Disables line buffering.
     *
     * Implemented by <code>cbreak</code>.
     */
    void cBreak() { ::cbreak(); }
    /**
     * @brief Disables input echoing.
     *
     * Implemented by <code>noecho</code>.
     */
    void noEcho() { ::noecho(); }
    /**
     * @brief Sets cursor behavior.
     *
     * @param[in] mode The new cursor mode.
     *
     * Implemented by <code>curs_set</code>.
     */
    void setCursor( int mode ) { ::curs_set( mode ); }
    /**
     * @brief Sets input timeout.
     *
     * @param[in] time The timeout value.
     *
     * Implemented by <code>timeout</code>.
     */
    void setTimeout( int time ) { ::timeout( time ); }
};

}} // cgt::curses

#endif /* !__CGT__CURSES__LIB_INIT_H__INCL__ */
