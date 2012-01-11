/**
 * @file config/ArgvParser.cpp
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#include "cgt-common.h"

#include "config/ArgvParser.h"
#include "config/ConfigMgr.h"

using namespace cgt;
using namespace cgt::config;

/*************************************************************************/
/* cgt::config::ArgvParser                                               */
/*************************************************************************/
ArgvParser::ArgvParser( ConfigMgr& configMgr )
: mConfigMgr( configMgr )
{
}

bool ArgvParser::parse( int argc, char* argv[] )
{
    for( int i = 1; i < argc; ++i )
    {
        char* opt = argv[ i ];

        if( '-' == *opt++ )
            // Lookup the option
            if( !parseShort( *opt, opt + 1 ) )
                return false;
    }

    return true;
}

bool ArgvParser::parseShort( char key, char* val )
{
    switch( key )
    {
        case 'D':
        {
            // Find '=' sign
            char* eq = ::strchr( val, '=' );
            if( NULL == eq )
            {
                ::printf( "No '=' in '%s'\n", val );
                return false;
            }

            // Split the string at '='
            *eq++ = '\0';

            // Import the config value
            mConfigMgr[ val ] = eq;
            return true;
        }
    }

    // Print an error message
    ::printf( "Unknown option '-%c'\n", key );
    return false;
}
