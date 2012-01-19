/**
 * @file config/XmlParser.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "config/ConfigMgr.h"
#include "config/XmlParser.h"

using namespace cgt;
using namespace cgt::config;

/*************************************************************************/
/* cgt::config::XmlParser                                                */
/*************************************************************************/
bool XmlParser::VisitEnter( const TiXmlElement& element,
                            const TiXmlAttribute* attribute )
{
    // Append a dot if the key is non-empty
    if( !mConfigKey.empty() )
        mConfigKey += '.';

    // Append the name of the element to the config key
    mConfigKey += element.ValueStr();

    // Iterate over all attributes
    for(; NULL != attribute; attribute = attribute->Next() )
        // Import the config value
        sConfigMgr[ mConfigKey + '.' + attribute->NameTStr() ] =
            attribute->ValueStr();

    // Visit children
    return true;
}

bool XmlParser::VisitExit( const TiXmlElement& element )
{
    // See if the key is longer than the element name
    if( element.ValueStr().length() < mConfigKey.length() )
        // Erase the suffix with the dot
        mConfigKey.erase( mConfigKey.length() - element.ValueStr().length() - 1 );
    else
        // Clear the config key
        mConfigKey.clear();

    // Parsing successful
    return true;
}

bool XmlParser::Visit( const TiXmlText& text )
{
    // Import the config value
    sConfigMgr[ mConfigKey ] = text.ValueStr();
    // No error occurred
    return true;
}
