/**
 * @file db/TextValue.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "db/TextValue.h"

using namespace cgt;
using namespace cgt::db;

/*************************************************************************/
/* cgt::db::TextValue                                                    */
/*************************************************************************/
TextValue::operator int64() const
{
    int64 v = 0;

    // Check for NULL.
    if( !isNull() )
    {
        // Use sscanf with SCNd64.
        int code = ::sscanf( mValue, "%"SCNd64, &v );
        assert( 1 == code );
    }

    return v;
}

TextValue::operator uint64() const
{
    uint64 v = 0;

    // Check for NULL.
    if( !isNull() )
    {
        // Use sscanf with SCNu64.
        int code = ::sscanf( mValue, "%"SCNu64, &v );
        assert( 1 == code );
    }

    return v;
}

TextValue::operator double() const
{
    double v = 0;

    // Check for NULL.
    if( !isNull() )
    {
        // Use plain sscanf.
        int code = ::sscanf( mValue, "%lf", &v );
        assert( 1 == code );
    }

    return v;
}

void TextValue::bind( int64 value )
{
    // More than enough, just to be on the safe side.
    char str[ 0x20 ];

    // Print the value.
    int code = ::sprintf( str, "%"PRId64, value );
    assert( 0 <= code );

    // Pretend it's a binary value, don't forget the terminating \0.
    return bind( reinterpret_cast< const uint8* >( str ), code + 1 );
}

void TextValue::bind( uint64 value )
{
    // More than enough, just to be on the safe side.
    char str[ 0x20 ];

    // Print the value.
    int code = ::sprintf( str, "%"PRIu64, value );
    assert( 0 <= code );

    // Pretend it's a binary value, don't forget the terminating \0.
    return bind( reinterpret_cast< const uint8* >( str ), code + 1 );
}

void TextValue::bind( double value )
{
    // More than enough, just to be on the safe side.
    char str[ 0x200 ];

    // Print the value.
    int code = ::sprintf( str, "%f", value );
    assert( 0 <= code );

    // Pretend it's a binary value, don't forget the terminating \0.
    return bind( reinterpret_cast< const uint8* >( str ), code + 1 );
}

void TextValue::bind( const uint8* value, size_t len )
{
    // Check if we have anything to do.
    if( !isNull() || 0 != len )
    {
        // Reallocate the value buffer.
        mValue = reinterpret_cast< char* >( ::realloc( mValue, len ) );
        // Copy the value.
        ::memcpy( mValue, value, len );
    }
}
