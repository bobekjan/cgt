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
     * @param[in] tone The tone.
     * @param[in] harm Harmonic index of the tone.
     */
    void print( const util::Tone& tone, unsigned int harm );
    /**
     * @brief Prints the note list.
     */
    void refresh();
};

}} // cgt::curses

#endif /* !__CGT__CURSES__NOTE_LIST_H__INCL__ */
