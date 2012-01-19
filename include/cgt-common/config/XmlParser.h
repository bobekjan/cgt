/**
 * @file config/XmlParser.h
 *
 * Console Guitar Tuner (CGT)
 * Copyright (c) 2011 by Bloody.Rabbit
 *
 * @author Bloody.Rabbit
 */

#ifndef __CGT__CONFIG__XML_PARSER_H__INCL__
#define __CGT__CONFIG__XML_PARSER_H__INCL__

namespace cgt { namespace config {

/**
 * @brief Parser for XML-based config files.
 *
 * @author Bloody.Rabbit
 */
class XmlParser
: public TiXmlVisitor
{
public:
    /**
     * @brief Visit an element.
     */
    bool VisitEnter( const TiXmlElement& element,
                     const TiXmlAttribute* attribute );
    /**
     * @brief Visit an element.
     */
    bool VisitExit( const TiXmlElement& element );

    /**
     * @brief Visit a text node.
     */
    bool Visit( const TiXmlText& text );

protected:
    /// Current config key.
    std::string mConfigKey;
};

}} // cgt::config

#endif /* !__CGT__CONFIG__XML_PARSER_H__INCL__ */
