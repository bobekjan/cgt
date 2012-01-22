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

namespace cgt { namespace curses {

/**
 * @brief A list of active configuration.
 *
 * @author Bloody.Rabbit
 */
class ConfigList
{
public:
    /**
     * @brief Initializes the config list.
     *
     * @param[in] row Row number of top left corner.
     * @param[in] col Column number of top left corner.
     */
    ConfigList( int row, int col );

    /**
     * @brief Prints the config list.
     */
    void print();

protected:
    /**
     * @brief Prints config parameter.
     *
     * @param[in] line  Line at which to print.
     * @param[in] title Title of the parameter.
     * @param[in] value Value of the parameter.
     */
    void print( int line, const char* title, const char* value );

    /// Position on the screen.
    int mRow, mCol;
};

}} // cgt::curses

#endif /* !__CGT__CURSES__CONFIG_LIST_H__INCL__ */
