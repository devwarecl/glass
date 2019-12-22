//
//#pragma once
//
//#ifndef __wcl_xml_document_hpp__
//#define __wcl_xml_document_hpp__
//
//#include <memory>
//#include <libxml/parser.h>
//#include "Node.hpp"
//
//namespace wcl {
//    namespace xml {
//
//        class Document {
//        public:
//            Document(xmlDocPtr document) {
//                this->document = document;
//            }
//
//            ~Document() {
//                ::xmlFreeDoc(document);
//            }
//
//            NodeRef GetRootNode() const {
//                return ::xmlDocGetRootElement(document);
//            }
//
//        private:
//            xmlDocPtr document=nullptr;
//        };
//    }
//}
//
//#endif
