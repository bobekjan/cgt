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

#include "config/XmlParser.h"

namespace cgt { namespace config {

/**
 * @brief Parser for command line args.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser
{
public:
    // An options' interface.
    class IOption;

    // Default option classes.
    class Option;
    class ConfigOption;
    class FlagOption;
    class HelpOption;
    class ValueOption;

    /// A set of options.
    typedef std::set< IOption* > OptionSet;
    /// A map of short options.
    typedef std::map< char, IOption* > ShortoptMap;
    /// A map of long options.
    typedef std::map< std::string, IOption* > LongoptMap;

    /**
     * @brief Removes all registered options.
     */
    ~ArgvParser() { clear(); }

    /**
     * @brief Adds a new option.
     *
     * @a opt is automatically garbage-collected
     * by ArgvParser.
     *
     * @param[in] opt The option to add.
     */
    void add( IOption* opt );
    /**
     * @brief Adds a new flag option.
     *
     * @param[in] shortKey    The short key of the option.
     * @param[in] longKey     The long key of the option.
     * @param[in] configKey   The flag's configuration key.
     * @param[in] description Description of the option.
     * @param[in] value       The value to set.
     */
    void addFlag( char shortKey, const char* longKey,
                  const char* configKey, const char* description,
                  bool value );
    /**
     * @brief Adds a new value option.
     *
     * @param[in] shortKey    The short key of the option.
     * @param[in] longKey     The long key of the option.
     * @param[in] configKey   The flag's configuration key.
     * @param[in] description Description of the option.
     */
    void addValue( char shortKey, const char* longKey,
                   const char* configKey, const char* description );

    /**
     * @brief Adds a new config option.
     */
    void addConfig();
    /**
     * @brief Adds a new help option.
     */
    void addHelp();

    /**
     * @brief Removes an option.
     *
     * @param[in] opt The option to remove.
     */
    void remove( IOption* opt );
    /**
     * @brief Removes an option by its short key.
     *
     * @param[in] key The short key of the option.
     */
    void remove( char key );
    /**
     * @brief Removes an option by its long key.
     *
     * @param[in] key The long key of the option.
     */
    void remove( const char* key );
    /**
     * @brief Removes all options.
     */
    void clear();

    /**
     * @brief Parses the arguments.
     *
     * @param[in] argc Number of arguments.
     * @param[in] argv The array of arguments.
     *
     * @return Number of consumed args.
     */
    unsigned int parse( unsigned int argc, char* argv[] );

protected:
    /**
     * @brief Parses a short option.
     *
     * @param[in] key  The key character.
     * @param[in] argc Number of arguments.
     * @param[in] argv The array of arguments.
     *
     * @return Number of consumed args.
     */
    unsigned int parse( char key, unsigned int argc, char* argv[] );
    /**
     * @brief Parses a long option.
     *
     * @param[in] key  The key string.
     * @param[in] argc Number of arguments.
     * @param[in] argv The array of arguments.
     *
     * @return Number of consumed args.
     */
    unsigned int parse( char* key, unsigned int argc, char* argv[] );

    /// A set of registered options.
    OptionSet   mOptions;
    /// A map with short options.
    ShortoptMap mShortopts;
    /// A map with long options.
    LongoptMap  mLongopts;
};

/**
 * @brief An ArgvParser's option's interface.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser::IOption
{
public:
    /**
     * @brief A virtual destructor.
     */
    virtual ~IOption() {}

    /**
     * @brief Checks if the option has a short key.
     *
     * @retval true  The option has a short key.
     * @retval false The option has no short key.
     */
    virtual bool hasShortKey() const = 0;
    /**
     * @brief Checks if the option has a long key.
     *
     * @retval true  The option has a long key.
     * @retval false The option has no long key.
     */
    virtual bool hasLongKey() const = 0;

    /**
     * @brief Obtains short key of the option.
     *
     * @return The short key.
     */
    virtual char shortKey() const = 0;
    /**
     * @brief Obtains long key of the option.
     *
     * @return The long key.
     */
    virtual const char* longKey() const = 0;
    /**
     * @brief Obtains description of the option.
     *
     * @return The description.
     */
    virtual const char* description() const = 0;

    /**
     * @brief Parses the option's arguments.
     *
     * @param[in] argc Number of available arguments.
     * @param[in] argv Vector of the arguments.
     *
     * @return Number of consumed args.
     */
    virtual unsigned int parse( unsigned int argc, char* argv[] ) = 0;
};

/**
 * @brief An ArgvParser's generic option.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser::Option
: public ArgvParser::IOption
{
public:
    /**
     * @brief Initializes basic option attributes.
     *
     * No strings are garbage-collected by this class
     * because they are assumed to be statically allocated.
     *
     * @param[in] shortKey    The short key.
     * @param[in] longKey     The long key.
     * @param[in] description The description.
     */
    Option( char shortKey, const char* longKey,
            const char* description );

    /**
     * @brief Checks if the short key is valid.
     *
     * A valid short key is non-zero.
     */
    bool hasShortKey() const { return '\0' != shortKey(); }
    /**
     * @brief Checks if the long key is valid.
     *
     * A valid long key is non-NULL and non-empty.
     */
    bool hasLongKey() const { return NULL != longKey() && '\0' != *longKey(); }

    /**
     * @brief Obtains the short key.
     */
    char shortKey() const { return mShortKey; }
    /**
     * @brief Obtains the long key.
     */
    const char* longKey() const { return mLongKey; }
    /**
     * @brief Obtains the description.
     */
    const char* description() const { return mDescription; }

protected:
    /// The short key.
    char mShortKey;
    /// The long key.
    const char* mLongKey;
    /// The description.
    const char* mDescription;
};

/**
 * @brief A config file option.
 *
 * Parses an XML-based config file.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser::ConfigOption
: public ArgvParser::Option
{
public:
    /**
     * @brief Initializes the config option.
     */
    ConfigOption();

    /**
     * @brief Parses the arguments.
     */
    unsigned int parse( unsigned int argc, char* argv[] );

protected:
    /// The config file parser.
    XmlParser mParser;
};

/**
 * @brief A simple flag option.
 *
 * Flips a config value on/off upon encountering
 * the flag.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser::FlagOption
: public ArgvParser::Option
{
public:
    /**
     * @brief Initializes the flag option.
     *
     * All strings are assumed to be statically allocated and
     * thus NOT freed.
     *
     * @param[in] shortKey    The short key of the option.
     * @param[in] longKey     The long key of the option.
     * @param[in] configKey   The flag's configuration key.
     * @param[in] description Description of the option.
     * @param[in] value       The value to set.
     */
    FlagOption( char shortKey, const char* longKey,
                const char* configKey, const char* description,
                bool value );

    /**
     * @brief Parses the arguments.
     */
    unsigned int parse( unsigned int argc, char* argv[] );

protected:
    /// The configuration key.
    const char* mConfigKey;
    /// The boolean value to set.
    bool mValue;
};

/**
 * @brief A print-help option.
 *
 * Prints all available options.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser::HelpOption
: public ArgvParser::Option
{
public:
    /**
     * @brief Initializes the help option.
     *
     * @param[in] parser The bound ArgvParser.
     */
    HelpOption( ArgvParser& parser );

    /**
     * @brief Parses the arguments.
     */
    unsigned int parse( unsigned int argc, char* argv[] );

protected:
    /// The bound ArgvParser.
    ArgvParser& mParser;
};

/**
 * @brief A simple value option.
 *
 * Sets a config value to a supplied argument.
 *
 * @author Bloody.Rabbit
 */
class ArgvParser::ValueOption
: public ArgvParser::Option
{
public:
    /**
     * @brief Initializes the value option.
     *
     * All strings are assumed to be statically allocated and
     * thus NOT freed.
     *
     * @param[in] shortKey    The short key of the option.
     * @param[in] longKey     The long key of the option.
     * @param[in] configKey   The flag's configuration key.
     * @param[in] description Description of the option.
     */
    ValueOption( char shortKey, const char* longKey,
                 const char* configKey, const char* description );

    /**
     * @brief Parses the arguments.
     */
    unsigned int parse( unsigned int argc, char* argv[] );

protected:
    /// The configuration key.
    const char* mConfigKey;
};

}} // cgt::config

#endif /* !__CGT__CONFIG__ARGV_PARSER_H__INCL__ */
