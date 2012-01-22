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
     * @brief Obtains color capability of the host terminal.
     *
     * Implemented by <code>has_colors</code>.
     *
     * @retval true  Colors available.
     * @retval false Colors unavailable.
     */
    bool hasColors() const { return ::has_colors(); }

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
     * @brief Starts color mode.
     *
     * Implemented by <code>start_color</code>.
     */
    void startColor() { ::start_color(); }
    /**
     * @brief Binds default colors to value -1.
     *
     * Implemented by <code>use_default_colors</code>.
     */
    void useDefaultColors() { ::use_default_colors(); }

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
