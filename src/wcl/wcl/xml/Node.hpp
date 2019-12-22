//
//#pragma once
//
//#ifndef __wcl_xml_node_hpp__
//#define __wcl_xml_node_hpp__
//
//#include <libxml/tree.h>
//#include <list>
//
//namespace wcl {
//
//    namespace xml {
//        class NodeRef;
//        typedef std::list<NodeRef> NodeRefList;
//
//        class NodeRef {
//        public:
//            NodeRef(::xmlNode *node) {
//                this->node = node;
//            }
//
//            std::string getName() const {
//                return (const char*)(this->node->name);
//            }
//
//            std::string getAttribute(const std::string &attrName) const {
//
//                const char* attribute = (const char*)(::xmlGetProp(this->node, (const xmlChar*)attrName.c_str()));
//
//                return attribute?std::string(attribute):"";
//            }
//
//            bool hasAttribute(const std::string &attrName) const {
//                const void* raw = (::xmlGetProp(this->node, (const xmlChar*) attrName.c_str()));
//                return raw != nullptr;
//            }
//
//            std::string getContent() const {
//                return (const char*)::xmlNodeGetContent(this->node);
//            }
//
//            NodeRefList getChilds() const {
//                NodeRefList childs;
//
//                for (::xmlNode *child=this->node->children; child; child=child->next) {
//                    if (child->type != XML_ELEMENT_NODE) {
//                        continue;
//                    }
//
//                    childs.push_back(child);
//                }
//
//                return childs;
//            }
//
//            NodeRefList getChilds(const std::string &name) const {
//                NodeRefList childs;
//
//                for (::xmlNode *child=this->node->children; child; child=child->next) {
//                    if (child->type != XML_ELEMENT_NODE) {
//                        continue;
//                    }
//
//                    if ( ::xmlStrcmp(child->name, (const xmlChar*)name.c_str()) == 0) {
//                        childs.push_back(child);
//                    }
//                }
//
//                return childs;
//            }
//
//            NodeRef getChild(const std::string &name) const {
//                NodeRefList childs = this->getChilds(name);
//
//                if (childs.size() == 0) {
//                    throw std::runtime_error("No child with the name '" + name + "'");
//                }
//            
//                return *childs.begin();
//            }
//        
//
//            bool IsEmpty() const {
//                return !this->node;
//            }
//
//        private:
//            ::xmlNode *node = nullptr;
//        };
//    }
//}
//
//#endif    
