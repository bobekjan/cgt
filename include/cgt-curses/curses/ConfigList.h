/**
 * @file curses/ConfigList.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CURSES__CONFIG_LIST_H__INCL__
#define __CGT__CURSES__CONFIG_LIST_H__INCL__

#include "curses/Window.h"

namespace cgt { namespace curses {

/**
 * @brief A list of active configuration.
 *
 * @author Bloody.Rabbit
 */
class ConfigList
: protected Window
{
public:
    /**
     * @brief Initializes the config list.
     *
     * @param[in] xpos   Position in X-axis.
     * @param[in] ypos   Position in Y-axis.
     * @param[in] width  Size in X-axis.
     * @param[in] height Size in Y-axis.
     */
    ConfigList( int xpos, int ypos, int width, int height );

    /**
     * @brief Prints the config list.
     */
    void refresh();

protected:
    /**
     * @brief Prints config parameter.
     *
     * @param[in] line  Line at which to print.
     * @param[in] title Title of the parameter.
     * @param[in] value Value of the parameter.
     */
    void addLine( int line, const char* title, const char* value );
};

}} // cgt::curses

#endif /* !__CGT__CURSES__CONFIG_LIST_H__INCL__ */
