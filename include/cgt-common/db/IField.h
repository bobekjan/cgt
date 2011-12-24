/**
 * @file db/IField.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__DB__IFIELD_H__INCL__
#define __CGT__DB__IFIELD_H__INCL__

namespace cgt { namespace db {

/**
 * @brief A database field.
 *
 * Basically a single value with run-time type.
 *
 * @author Bloody.Rabbit
 */
class IField
{
public:
    /**
     * @brief Checks if the field is NULL.
     *
     * @retval true  The field is NULL.
     * @retval false The field is not NULL.
     */
    virtual bool isNull() const = 0;
    /**
     * @brief Obtains current width of the field, in bytes.
     *
     * @return The width of the field.
     */
    virtual unsigned long width() const = 0;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    template< typename T >
    T as() const { return static_cast< T >( *this ); }

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator bool() const = 0;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator int8() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator int16() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator int32() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator int64() const = 0;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator uint8() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator uint16() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator uint32() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator uint64() const = 0;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator float() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator double() const = 0;

    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator const uint8*() const = 0;
    /**
     * @brief Obtains the value in the field.
     *
     * @return The value in the field.
     */
    virtual operator const char*() const = 0;
};

}} // cgt::db

#endif /* !__CGT__DB__IFIELD_H__INCL__ */
