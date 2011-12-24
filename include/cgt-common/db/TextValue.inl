/**
 * @file db/TextValue.inl
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

/*************************************************************************/
/* cgt::db::TextValue                                                    */
/*************************************************************************/
inline TextValue::TextValue()
: mValue( NULL )
{
}

template< typename T >
inline TextValue::TextValue( const T& value )
: mValue( NULL )
{
    // Use assignment operator.
    *this = value;
}

inline TextValue::TextValue( const TextValue& oth )
: mValue( NULL )
{
    // Use assignment operator.
    *this = oth;
}

inline TextValue::~TextValue()
{
    // Bind NULL, deleting the value.
    bool success = bindNull();
    assert( success );
}

inline TextValue::operator const uint8*() const
{
    // Simple reinterpret_cast the string.
    return reinterpret_cast< const uint8* >( as< const char* >() );
}

inline bool TextValue::bind( const char* value )
{
    // Pretend it's a binary value, don't forget the terminating \0.
    return bind( reinterpret_cast< const uint8* >( value ),
                 NULL != value ? ::strlen( value ) + 1 : 0 );
}

template< typename T >
inline TextValue& TextValue::operator=( const T& value )
{
    // Redirect the assignment to proper overload of bind.
    bool success = bind( value );
    assert( success );

    return *this;
}

inline TextValue& TextValue::operator=( const TextValue& value )
{
    // Use bind for the assignment.
    bool success = bind( value.mValue );
    assert( success );

    return *this;
}
