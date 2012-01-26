/**
 * @file cgt-compat.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

/*************************************************************************/
/* Text processing                                                       */
/*************************************************************************/
std::string ssprintf( const char* fmt, ... )
{
    // String buffer
    std::string str;

    // Start argument list
    va_list ap;
    va_start( ap, fmt );

    // Print the string
    ::vssprintf( str, fmt, ap );

    // End argument list
    va_end( ap );

    // Return the string
    return str;
}

std::string vssprintf( const char* fmt, va_list ap )
{
    // String buffer
    std::string str;

    // Print the string
    ::vssprintf( str, fmt, ap );

    // Return the string
    return str;
}

void ssprintf( std::string& str, const char* fmt, ... )
{
    // Start argument list
    va_list ap;
    va_start( ap, fmt );

    // Print the string
    ::vssprintf( str, fmt, ap );

    // End argument list
    va_end( ap );
}

void vssprintf( std::string& str, const char* fmt, va_list ap )
{
    // Obtain initial offset
    size_t off = str.length();
    // Initial size (will be doubled)
    size_t size = 0x40 >> 1;
    // Print return code
    int code;

    do
    {
        // Double the size
        size <<= 1;
        // Resize the buffer
        str.resize( off + size );

        // Print to the buffer
        code = ::vsnprintf( &str[off], str.length() - off, fmt, ap );
        // Check for truncation
        if( str.length() <= off + code )
            // Output truncated
            code = -1;

    } while( 0 > code );

    // Resize the string properly not to waste space
    str.resize( off + code + 1 );
}
