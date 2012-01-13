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

int ArgvParser::parse( int argc, char* argv[] )
{
    // Offset in argv, also return code
    int off = 0;

    // Skip the first element (executable name)
    for( int idx = 1; idx < argc; ++idx )
    {
        // This has to be a reference
        char*& opt = argv[ idx ];

        if( '-' == *opt++ )
        {
            // Parser return code
            int code = 0;

            do
            {
                // Process the option
                code = parse( *opt++, argc - idx, argv + idx );

                // Check the return value
                if( 0 > code )
                    // Negative error
                    return code;
                else if( '\0' == *opt )
                    // No more options to process
                    code = 1;

            } while( 0 == code );

            // Rotate the processed arguments
            std::rotate( argv + off,
                         argv + idx,
                         argv + idx + code );

            // Shift offset and index appropriately
            off += code;
            idx += code - 1;
        }
    }

    return off;
}

int ArgvParser::parse( char key, int argc, char* argv[] )
{
    // Check for longopt
    if( '-' == key )
    {
        // Obtain name
        char* name = *argv;

        // Try to find '='
        char* val = ::strchr( name, '=' );
        if( NULL == val )
        {
            // Parse it, skipping entire name
            int code = parse( name, argc - 1, argv + 1 );

            // Check the return value
            return 0 > code ? code : code + 1;
        }
        else
        {
            // Split the name at '='
            *val++ = '\0';
            // Replace the argument with value
            *argv = val;

            // Parse it
            return parse( name, argc, argv );
        }
    }

    // Print an error message
    ::printf( "Unknown option '-%c'\n", key );
    return -1;
}

int ArgvParser::parse( char* key, int argc, char* argv[] )
{
    // Check if we have a value
    if( 0 == argc )
    {
        ::printf( "No value for option '--%s'\n", key );
        return -1;
    }

    // Set the option
    mConfigMgr[ key ] = *argv;
    return 1;
}
