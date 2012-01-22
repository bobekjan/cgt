/**
 * @file util/Harmonics.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "util/Harmonics.h"

using namespace cgt;
using namespace cgt::util;

/*************************************************************************/
/* cgt::util::Harmonics                                                  */
/*************************************************************************/
Harmonics::Harmonics( double tol )
: mTolerance( tol )
{
}

unsigned int Harmonics::get( double freq )
{
    std::vector< double >::const_iterator cur, end;
    cur = mFundamentals.begin();
    end = mFundamentals.end();
    for(; cur != end; ++cur )
    {
        // Calculate ratio of the frequencies.
        double ratio = freq / *cur;
        // Round it to the nearest integer.
        int k = ratio + 0.5;

        // If the error is small enough, return the ratio.
        if( tolerance() > 10 * ::log10( ::fabs( ratio - k ) ) )
            return k - 1;
    }

    // Add a new fundamental.
    mFundamentals.push_back( freq );
    return 0;
}

void Harmonics::clear()
{
    // Clear fundamentals.
    mFundamentals.clear();
}
