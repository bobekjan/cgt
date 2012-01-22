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

namespace cgt { namespace curses {

/**
 * @brief A list of notes.
 *
 * @author Bloody.Rabbit
 */
class NoteList
{
public:
    /**
     * @brief Initializes the note list.
     *
     * @param[in] row    Row number of top left corner.
     * @param[in] col    Column number of top left corner.
     * @param[in] width  Width of the list.
     * @param[in] height Height of the list.
     */
    NoteList( int row, int col );

    /**
     * @brief Adds a note to the list.
     *
     * @param[in] freq Frequency of the note.
     * @param[in] harm Harmonic index of the note.
     */
    void add( double freq, unsigned int harm );
    /**
     * @brief Clears the note list.
     */
    void clear();

protected:
    /// A buffer for note name.
    char mName[ 0x20 ];

    /// Position on the screen.
    int mRow, mCol;
};

}} // cgt::curses

#endif /* !__CGT__CURSES__NOTE_LIST_H__INCL__ */
