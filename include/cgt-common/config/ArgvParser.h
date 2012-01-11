/**
 * @file config/ArgvParser.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CONFIG__ARGV_PARSER_H__INCL__
#define __CGT__CONFIG__ARGV_PARSER_H__INCL__

namespace cgt { namespace config {

class ConfigMgr;

/**
 * @brief Parser for command line args.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser
{
public:
    /**
     * @brief Initializes the parser.
     *
     * @param[in] configMgr The bound config manager.
     */
    ArgvParser( ConfigMgr& configMgr );

    /**
     * @brief Parser the arguments.
     *
     * @param[in] argc Number of arguments.
     * @param[in] argv The array of arguments.
     *
     * @retval true  Parsing successful.
     * @retval false Parsing failed.
     */
    bool parse( int argc, char* argv[] );

protected:
    /**
     * @brief Parses short option.
     *
     * @param[in] key The key character.
     * @param[in] val Value of the option
     *
     * @retval true  Parsing successful.
     * @retval false Parsing failed.
     */
    bool parseShort( char key, char* val );

    /// Where the parsed options will be stored.
    ConfigMgr& mConfigMgr;
};

}} // cgt::config

#endif /* !__CGT__CONFIG__ARGV_PARSER_H__INCL__ */
