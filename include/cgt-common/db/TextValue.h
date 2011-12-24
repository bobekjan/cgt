/**
 * @file db/TextValue.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__DB__TEXT_VALUE_H__INCL__
#define __CGT__DB__TEXT_VALUE_H__INCL__

#include "db/IField.h"
#include "db/IParameter.h"

namespace cgt { namespace db {

/**
 * @brief A text value.
 *
 * Any value assigned is converted to
 * text form for storage.
 *
 * @author Bloody.Rabbit
 */
class TextValue
: public IField,
  public IParameter
{
public:
    /**
     * @brief Initializes an empty value.
     */
    TextValue();
    /**
     * @brief Initializes the text value.
     *
     * @param[in] value The value.
     */
    template< typename T >
    TextValue( const T& value );
    /**
     * @brief Duplicates the value.
     *
     * @param[in] oth The other text value.
     */
    TextValue( const TextValue& oth );
    /**
     * @brief Deletes the stored value.
     */
    ~TextValue();

    /**
     * @brief Checks if the field is NULL.
     */
    bool isNull() const { return NULL == mValue; }
    /**
     * @brief Obtains current width of the field, in bytes.
     */
    unsigned long width() const { return !isNull() ? ::strlen( mValue ) + 1 : 0; }

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator bool() const { return as< int8 >(); }

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator int8() const { return as< int16 >(); }
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator int16() const { return as< int32 >(); }
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator int32() const { return as< int64 >(); }
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator int64() const;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator uint8() const { return as< uint16 >(); }
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator uint16() const { return as< uint32 >(); }
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator uint32() const { return as< uint64 >(); }
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator uint64() const;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator float() const { return as< double >(); }
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator double() const;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator const uint8*() const;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    operator const char*() const { return mValue; }

    /**
     * @brief Binds NULL to the parameter.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bindNull() { return bind( NULL, 0 ); }

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( bool value ) { return bind( static_cast< int8 >( value ) ); }

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( int8 value ) { return bind( static_cast< int16 >( value ) ); }
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( int16 value ) { return bind( static_cast< int32 >( value ) ); }
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( int32 value ) { return bind( static_cast< int64 >( value ) ); }
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( int64 value );

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( uint8 value ) { return bind( static_cast< uint16 >( value ) ); }
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( uint16 value ) { return bind( static_cast< uint32 >( value ) ); }
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( uint32 value ) { return bind( static_cast< uint64 >( value ) ); }
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( uint64 value );

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( float value ) { return bind( static_cast< double >( value ) ); }
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( double value );

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     * @param[in] len   Length of the value.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( const uint8* value, size_t len );
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( const char* value );
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    bool bind( const std::string& value ) { return bind( value.c_str() ); }

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @return Itself.
     */
    template< typename T >
    TextValue& operator=( const T& value );
    /**
     * @brief Copies a value from other value.
     *
     * @param[in] oth The other value.
     *
     * @return Itself.
     */
    TextValue& operator=( const TextValue& oth );

protected:
    /// The text value.
    char* mValue;
};

// Include inline code.
#include "db/TextValue.inl"

}} // cgt::db


#endif /* !__CGT__DB__TEXT_VALUE_H__INCL__ */
