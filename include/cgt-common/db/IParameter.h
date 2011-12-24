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
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bindNull() = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( bool value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( int8 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( int16 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( int32 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( int64 value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( uint8 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( uint16 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( uint32 value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( uint64 value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( float value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( double value ) = 0;

    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     * @param[in] len   Length of the value.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( const uint8* value, size_t len ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( const char* value ) = 0;
    /**
     * @brief Binds a value to the parameter.
     *
     * @param[in] value The value to bind.
     *
     * @retval true  Bind successful.
     * @retval false Bind failed.
     */
    virtual bool bind( const std::string& value ) = 0;

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
        bool success = bind( value );
        assert( success );

        return *this;
    }
};

}} // cgt::db

#endif /* !__CGT__DB__IPARAMETER_H__INCL__ */
