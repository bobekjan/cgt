/**
 * @file db/IParameter.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__DB__IPARAMETER_H__INCL__
#define __CGT__DB__IPARAMETER_H__INCL__

namespace cgt { namespace db {

/**
 * @brief A parameter of a statement.
 *
 * @author Bloody.Rabbit
 */
class IParameter
{
public:
    /**
     * @brief Binds NULL to the parameter.
     */
    virtual void bindNull() = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( bool value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( int8 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( int16 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( int32 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( int64 value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( uint8 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( uint16 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( uint32 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( uint64 value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( float value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( double value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     * @param[in] len   Length of the value.
     */
    virtual void bind( const uint8* value, size_t len ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( const char* value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     */
    virtual void bind( const std::string& value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @return Itself.
     */
    template< typename T >
    IParameter& operator=( const T& value )
    {
        // Bind the value
        bind( value );
        // Return itself
        return *this;
    }
};

}} // cgt::db

#endif /* !__CGT__DB__IPARAMETER_H__INCL__ */
