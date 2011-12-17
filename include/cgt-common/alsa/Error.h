/**
 * @file alsa/Error.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__ALSA__ERROR_H__INCL__
#define __CGT__ALSA__ERROR_H__INCL__

namespace cgt {
/**
 * @brief Contains ALSA interface utilities.
 *
 * @author Bloody.Rabbit
 */
namespace alsa {

/**
 * @brief An ALSA error.
 *
 * @author Bloody.Rabbit
 */
class Error
{
public:
    /**
     * @brief The primary constructor.
     *
     * @param[in] code The error code.
     */
    Error( int code = 0 );

    /**
     * @brief Obtains the ALSA error code.
     *
     * @return The numerical error code.
     */
    int code() const { return mCode; }
    /**
     * @brief Obtains an ALSA error description.
     *
     * Implemented by <code>snd_strerror</code>.
     *
     * @return A textual error description.
     */
    const char* what() const;

    /**
     * @brief Determines if an error occurred.
     *
     * @retval true  An error occurred.
     * @retval false No error occurred.
     */
    operator bool() const { return 0 > code(); }

protected:
    /// The ALSA error code.
    int mCode;
};

// Simple wrapper, all methods are inlined.
#include "alsa/Error.inl"

}} // cgt::alsa

#endif /* !__CGT__ALSA__ERROR_H__INCL__ */
