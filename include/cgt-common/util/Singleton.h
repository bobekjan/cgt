/**
 * @file util/Singleton.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__UTIL__SINGLETON_H__INCL__
#define __CGT__UTIL__SINGLETON_H__INCL__

namespace cgt { namespace util {

/**
 * @brief Template used for singleton classes.
 *
 * This template shall be used as base for classes
 * which are intended to be singleton (i.e. there
 * should be only 1 instance of this class at all).
 *
 * @author Bloody.Rabbit
 */
template< typename T >
class Singleton
{
public:
    /**
     * @brief Primary constructor.
     *
     * Checks if the instance being constructed is first, i.e.
     * mInstance hasn't been filled yet. This only makes sense
     * if the actual class is derived from Singleton.
     */
    Singleton()
    {
        assert( NULL == mInstance.get() );
    }

    /**
     * @brief Obtains the singleton instance.
     *
     * Uses lazy construction (i.e. object is constructed
     * on first access request).
     *
     * @return The singleton instance.
     */
    static T& get()
    {
        if( NULL == mInstance.get() )
            mInstance.reset( new T );

        return *mInstance;
    }

protected:
    /// Pointer to the singleton instance.
    static std::auto_ptr< T > mInstance;
};

template< typename T >
std::auto_ptr< T > Singleton< T >::mInstance( NULL );

}} // namespace cgt::util

#endif /* !__CGT__UTIL__SINGLETON_H__INCL__ */
