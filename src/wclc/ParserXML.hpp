
#pragma once 

#ifndef __wclc_parser_xml_hpp__
#define __wclc_parser_xml_hpp__

#include "Parser.hpp"

#include <wcl/xml/Document.hpp>

namespace wclc {
    class ParserXML : public Parser {
    public:
        ParserXML();
        ParserXML(wcl::xml::NodeRef node);

        void setRootElement(wcl::xml::NodeRef root);

        Frame parse() override;

    private:
        wcl::xml::NodeRef root;
    };
}

#endif
