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
void ArgvParser::add( IOption* opt )
{
    // Add it to the global register
    mOptions.insert( opt );

    // Add it to shortopts
    if( opt->hasShortKey() )
    {
        // Remove any previous option with identical key
        remove( opt->shortKey() );
        // Insert it to the map
        mShortopts[ opt->shortKey() ] = opt;
    }

    // Add it to longopts
    if( opt->hasLongKey() )
    {
        // Remove any previous option with identical key
        remove( opt->longKey() );
        // Insert it to the map
        mLongopts[ opt->longKey() ] = opt;
    }
}

void ArgvParser::addFlag( char shortKey, const char* longKey,
                          const char* configKey, const char* description,
                          bool value )
{
    add( new FlagOption( shortKey, longKey, configKey, description, value ) );
}

void ArgvParser::addValue( char shortKey, const char* longKey,
                           const char* configKey, const char* description )
{
    add( new ValueOption( shortKey, longKey, configKey, description ) );
}

void ArgvParser::addHelp()
{
    add( new HelpOption( *this ) );
}

void ArgvParser::remove( IOption* opt )
{
    // Remove it from shortopts
    if( opt->hasShortKey() )
        mShortopts.erase( opt->shortKey() );

    // Remove it from longopts
    if( opt->hasLongKey() )
        mLongopts.erase( opt->longKey() );

    // Remove it from the global register
    mOptions.erase( opt );
    // Delete it
    util::safeDelete( opt );
}

void ArgvParser::remove( char key )
{
    // Lookup the option
    ShortoptMap::const_iterator itr = mShortopts.find( key );
    if( mShortopts.end() != itr )
        // Remove it
        remove( itr->second );
}

void ArgvParser::remove( const char* key )
{
    // Lookup the option
    LongoptMap::const_iterator itr = mLongopts.find( key );
    if( mLongopts.end() != itr )
        // Remove it
        remove( itr->second );
}

void ArgvParser::clear()
{
    // Clear all shortopts
    mShortopts.clear();
    // Clear all longopts
    mLongopts.clear();

    // Iterate over the global register
    OptionSet::iterator cur, end;
    cur = mOptions.begin();
    end = mOptions.end();
    for(; cur != end; ++cur )
        // Delete the option
        delete *cur;

    // Clear the global register
    mOptions.clear();
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

    // Find appropriate parser
    ShortoptMap::const_iterator itr = mShortopts.find( key );
    if( mShortopts.end() == itr )
    {
        // Print an error message
        ::printf( "Unknown shortopt '-%c'\n", key );
        return -1;
    }

    // Check first string
    if( '\0' == **argv )
    {
        // It has been consumed, shift arguments
        int code = itr->second->parse( argc - 1, argv + 1 );

        // Check return value
        return 0 > code ? code : code + 1;
    }
    else
        // Parse as-is
        return itr->second->parse( argc, argv );
}

int ArgvParser::parse( char* key, int argc, char* argv[] )
{
    // Find appropriate parser
    LongoptMap::const_iterator itr = mLongopts.find( key );
    if( mLongopts.end() == itr )
    {
        // Print an error message
        ::printf( "Unknown longopt '--%s'\n", key );
        return -1;
    }

    // Parse as-is
    return itr->second->parse( argc, argv );
}

/*************************************************************************/
/* cgt::config::ArgvParser::Option                                       */
/*************************************************************************/
ArgvParser::Option::Option( char shortKey, const char* longKey,
                            const char* description )
: mShortKey( shortKey ),
  mLongKey( longKey ),
  mDescription( description )
{
}

/*************************************************************************/
/* cgt::config::ArgvParser::FlagOption                                   */
/*************************************************************************/
ArgvParser::FlagOption::FlagOption( char shortKey, const char* longKey,
                                    const char* configKey, const char* description,
                                    bool value )
: ArgvParser::Option( shortKey, longKey, description ),
  mConfigKey( configKey ),
  mValue( value )
{
}

int ArgvParser::FlagOption::parse( int, char*[] )
{
    // Set the flag
    sConfigMgr[ mConfigKey ] = mValue;

    // No arguments to consume
    return 0;
}

/*************************************************************************/
/* cgt::config::ArgvParser::HelpOption                                   */
/*************************************************************************/
ArgvParser::HelpOption::HelpOption( ArgvParser& parser )
: ArgvParser::Option( 'h', "help", "Print all available options" ),
  mParser( parser )
{
}

int ArgvParser::HelpOption::parse( int, char*[] )
{
    // Print initial line
    ::puts( "Available options:" );

    // Iterate over all options of the parser
    OptionSet::const_iterator cur, end;
    cur = mParser.mOptions.begin();
    end = mParser.mOptions.end();
    for(; cur != end; ++cur )
    {
        IOption* opt = *cur;

        if( !opt->hasShortKey() )
            // Print only with long key
            ::printf( "      --%s\t\t%s\n",
                      opt->longKey(), opt->description() );
        else if( !opt->hasLongKey() )
            // Print only with short key
            ::printf( "  -%c\t\t\t%s\n",
                      opt->shortKey(), opt->description() );
        else
            // Print with both keys
            ::printf( "  -%c, --%s\t\t%s\n", opt->shortKey(),
                      opt->longKey(), opt->description() );
    }

    // Return with failure to stop processing
    return -1;
}

/*************************************************************************/
/* cgt::config::ArgvParser::ValueOption                                  */
/*************************************************************************/
ArgvParser::ValueOption::ValueOption( char shortKey, const char* longKey,
                                      const char* configKey, const char* description )
: ArgvParser::Option( shortKey, longKey, description ),
  mConfigKey( configKey )
{
}

int ArgvParser::ValueOption::parse( int argc, char* argv[] )
{
    // Check if we have the required argument
    if( 1 > argc )
    {
        if( !hasShortKey() )
            // Print error message with long key only
            ::printf( "No value supplied for option '--%s'\n",
                      longKey() );
        else if( !hasLongKey() )
            // Print error message with short key only
            ::printf( "No value supplied for option '-%c'\n",
                      shortKey() );
        else
            // Print error message with both keys
            ::printf( "No value supplied for option '-%c/--%s'\n",
                      shortKey(), longKey() );

        // Return with an error
        return -1;
    }

    // Use the argument as a value
    sConfigMgr[ mConfigKey ] = *argv;

    // 1 argument consumed
    return 1;
}
