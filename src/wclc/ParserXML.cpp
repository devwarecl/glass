//
//#include "ParserXML.hpp"
//
//namespace wclc {
//
//    Accelerator ParseAccelerator(wcl::xml::NodeRef node) {
//        return {node.getAttribute("command"), node.getAttribute("shortcut")};
//    }
//
//    AcceleratorTable ParseAcceleratorTable(wcl::xml::NodeRef node) {
//        AcceleratorTable table;
//
//        for (wcl::xml::NodeRef child : node.getChilds("Accelerator")) {
//            table.accelerators.push_back(ParseAccelerator(child));
//        }
//
//        return table;
//    }
//
//    Menu ParseMenuSeparator(wcl::xml::NodeRef node) {
//        return {"", "-"};
//    }
//
//    Menu ParseMenu(wcl::xml::NodeRef node) {
//        Menu menu;
//
//        menu.command = node.getAttribute("command");
//        menu.text = node.getAttribute("text");
//    
//        for (wcl::xml::NodeRef child : node.getChilds()) {
//
//            std::string childName = child.getName();
//
//            if (childName == "Menu") {
//                menu.childs.push_back(ParseMenu(child));
//
//            } else if (childName == "MenuSeparator") {
//                menu.childs.push_back(ParseMenuSeparator(child));
//            }
//        }
//
//        return menu;
//    }
//
//    std::list<std::string> classes = {
//        "Window", "Button", "Static", "Edit", "Scintilla"
//    };
//
//    template<typename WindowSubClass>
//    WindowSubClass ParseWindowSubClass(wcl::xml::NodeRef node) {
//        WindowSubClass window;
//
//        window.windowClass = node.getAttribute("windowClass");
//        window.class_ = node.getAttribute("class");
//        window.name = node.getAttribute("name");
//        window.text = node.getAttribute("text");
//        window.rect = node.getAttribute("rect");
//        window.style = node.getAttribute("style");
//        window.exStyle  = node.getAttribute("exStyle");
//
//        for (wcl::xml::NodeRef child : node.getChilds("Window")) {
//            window.childs.push_back(ParseWindow(child));
//        }
//
//        return window;
//    }
//
//    Window ParseWindow(wcl::xml::NodeRef node) {
//        return ParseWindowSubClass<Window>(node);
//    }
//
//    Frame ParseFrame(wcl::xml::NodeRef node) {
//        Frame frame = ParseWindowSubClass<Frame>(node);
//
//        for (wcl::xml::NodeRef child : node.getChilds()) {
//            std::string childName = child.getName();
//
//            if (childName == "Menu") {
//                frame.menu = ParseMenu(child);
//            }
//
//            if (childName == "AcceleratorTable") {
//                frame.acceleratorTable = ParseAcceleratorTable(child);
//            }
//        }
//
//        return frame;
//    }
//
//    ParserXML::ParserXML() : root(nullptr) {}
//
//    ParserXML::ParserXML(wcl::xml::NodeRef node) : root(nullptr) {
//        this->setRootElement(node);
//    }
//
//    void ParserXML::setRootElement(wcl::xml::NodeRef node) {
//        this->root = node;
//    }
//
//    Frame ParserXML::parse() {
//        return ParseFrame(this->root);
//    }
//}
