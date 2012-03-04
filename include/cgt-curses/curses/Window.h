/**
 * @file curses/Window.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CURSES__WINDOW_H__INCL__
#define __CGT__CURSES__WINDOW_H__INCL__

namespace cgt { namespace curses {

/**
 * @brief A generic curses window.
 *
 * @author Bloody.Rabbit
 */
class Window
{
public:
    /**
     * @brief Initializes the window.
     *
     * Implemented by <code>newwin</code>.
     *
     * @param[in] xpos   Position in X-axis.
     * @param[in] ypos   Position in Y-axis.
     * @param[in] width  Size in X-axis.
     * @param[in] height Size in Y-axis.
     */
    Window( int xpos, int ypos, int width, int height );
    /**
     * @brief Destroys the window.
     */
    ~Window();

    /**
     * @brief Refreshes the window.
     *
     * Implemented by <code>wrefresh</code>.
     */
    void refresh() const;
    /**
     * @brief Prepares window for a manual refresh.
     *
     * Implemented by <code>wnoutrefresh</code>.
     */
    void noutRefresh() const;

    /**
     * @brief Moves the cursor within the window.
     *
     * Implemented by <code>wmove</code>.
     *
     * @param[in] xpos Position in X-axis.
     * @param[in] ypos Position in Y-axis.
     */
    void move( int xpos, int ypos );
    /**
     * @brief Turns on an attribute.
     *
     * Implemented by <code>wattron</code>.
     *
     * @param[in] attr The attribute.
     */
    void attrOn( int attr );
    /**
     * @brief Turns off an attribute.
     *
     * Implemented by <code>wattroff</code>.
     *
     * @param[in] attr The attribute.
     */
    void attrOff( int attr );
    /**
     * @brief Draws a box around the window.
     *
     * @param[in] verch Vertical character.
     * @param[in] horch Horizontal character.
     *
     * Implemented by <code>box</code>.
     */
    void box( int verch = 0, int horch = 0 );

    /**
     * @brief Adds a string to the window.
     *
     * Implemented by <code>waddstr</code>.
     *
     * @param[in] str The string to be printed.
     */
    void addStr( const char* str );
    /**
     * @brief Prints a string to the window.
     *
     * Implemented by <code>vwprintw</code>.
     *
     * @param[in] fmt The format string.
     * @param[in] ... Arguments of the string.
     */
    void printw( const char* fmt, ... );
    /**
     * @brief Prints a string to the window.
     *
     * Implemented by <code>vwprintw</code>.
     *
     * @param[in] fmt The format string.
     * @param[in] ap  Arguments of the string.
     */
    void vprintw( const char* fmt, va_list ap );

    /**
     * @brief Wipes content of the window.
     *
     * Implemented by <code>wclear</code>.
     */
    void clear();
    /**
     * @brief Wipes content of the window.
     *
     * Implemented by <code>werase</code>.
     */
    void erase();

protected:
    /// The wrapped window.
    WINDOW* mWindow;
};

// Include the inlined code
#include "curses/Window.inl"

}} // cgt::curses

#endif /* !__CGT__CURSES__WINDOW_H__INCL__ */
