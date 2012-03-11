/**
 * @file curses/MagnitudeBar.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CURSES__MAGNITUDE_BAR_H__INCL__
#define __CGT__CURSES__MAGNITUDE_BAR_H__INCL__

#include "curses/Window.h"

namespace cgt { namespace curses {

/**
 * @brief A magnitude bar.
 *
 * @author Bloody.Rabbit
 */
class MagnitudeBar
: protected Window
{
public:
    /**
     * @brief Initializes the magnitude bar.
     *
     * @param[in] xpos   Position in X-axis.
     * @param[in] ypos   Position in Y-axis.
     * @param[in] width  Size in X-axis.
     * @param[in] height Size in Y-axis.
     */
    MagnitudeBar( int xpos, int ypos, int width, int height );

    /**
     * @brief Add a magnitude to the list.
     *
     * @param[in] mag The magnitude.
     */
    void add( double mag );
    /**
     * @brief Reprints the magnitude bar.
     */
    void refresh();

protected:
    /// The configured cutoff.
    double mCutoff;
    /// The configured span.
    double mSpan;

    /// The maximum magnitude.
    stats::Maximum< double, double > mMax;
};

}} // cgt::curses

#endif /* !__CGT__CURSES__MAGNITUDE_BAR_H__INCL__ */
