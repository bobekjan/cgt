/**
 * @file config/ConfigMgr.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CONFIG__CONFIG_MGR_H__INCL__
#define __CGT__CONFIG__CONFIG_MGR_H__INCL__

#include "db/TextValue.h"
#include "util/Singleton.h"

namespace cgt { namespace config {

/**
 * @brief A configuration manager.
 *
 * Basically it's a map with
 * both keys and values being text.
 *
 * @author Bloody.Rabbit
 */
class ConfigMgr
: public util::Singleton< ConfigMgr >
{
public:
    /**
     * @brief Obtains a value from the config manager.
     *
     * @param[in] key The key identifying the value.
     *
     * @return The value in question.
     */
    db::TextValue& operator[]( const std::string& key ) { return mValues[ key ]; }

protected:
    /// The values map.
    std::map< std::string, db::TextValue > mValues;
};

/// A macro for convenient access.
#define sConfigMgr config::ConfigMgr::get()

}} // cgt::config

#endif /* !__CGT__CONFIG__CONFIG_MGR_H__INCL__ */
