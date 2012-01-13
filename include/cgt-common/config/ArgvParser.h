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
     * @brief Parses the arguments.
     *
     * @param[in] argc Number of arguments.
     * @param[in] argv The array of arguments.
     *
     * @return Number of consumed args; negative means error.
     */
    int parse( int argc, char* argv[] );

protected:
    /**
     * @brief Parses a short option.
     *
     * @param[in] key  The key character.
     * @param[in] argc Number of arguments.
     * @param[in] argv The array of arguments.
     *
     * @return Number of consumed args; negative means error.
     */
    int parse( char key, int argc, char* argv[] );
    /**
     * @brief Parses a long option.
     *
     * @param[in] key  The key string.
     * @param[in] argc Number of arguments.
     * @param[in] argv The array of arguments.
     *
     * @return Number of consumed args; negative means error.
     */
    int parse( char* key, int argc, char* argv[] );

    /// Where the parsed options will be stored.
    ConfigMgr& mConfigMgr;
};

}} // cgt::config

#endif /* !__CGT__CONFIG__ARGV_PARSER_H__INCL__ */
