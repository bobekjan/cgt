/**
 * @file curses/NoteList.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CURSES__NOTE_LIST_H__INCL__
#define __CGT__CURSES__NOTE_LIST_H__INCL__

#include "curses/Window.h"

namespace cgt { namespace curses {

/**
 * @brief A list of notes.
 *
 * @author Bloody.Rabbit
 */
class NoteList
: protected Window
{
public:
    /**
     * @brief Initializes the note list.
     *
     * @param[in] xpos   Position in X-axis.
     * @param[in] ypos   Position in Y-axis.
     * @param[in] width  Size in X-axis.
     * @param[in] height Size in Y-axis.
     */
    NoteList( int xpos, int ypos, int width, int height );

    /**
     * @brief Adds a note to the list.
     *
     * @param[in] freq Frequency of the note.
     * @param[in] harm Harmonic index of the note.
     */
    void print( double freq, unsigned int harm );
    /**
     * @brief Prints the note list.
     */
    void refresh();
    /**
     * @brief Clears the note list.
     */
    void clear();

protected:
    /// A buffer for note name.
    char mName[ 0x20 ];
};

}} // cgt::curses

#endif /* !__CGT__CURSES__NOTE_LIST_H__INCL__ */
