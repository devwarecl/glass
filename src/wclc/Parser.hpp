
#pragma once 

#ifndef __wclc_parser_hpp__
#define __wclc_parser_hpp__

#include <string>
#include <vector>
#include <list>

namespace wclc {

    struct Accelerator {
        std::string command;
        std::string shortcut;
    };

    struct AcceleratorTable {
        std::list<Accelerator> accelerators;
    };

    enum class MenuKind {
        Menu, 
        Item, 
        Separator
    };

    struct Menu {
        std::string command;
        std::string text;
        std::list<Menu> childs;

        MenuKind GetKind() const {
            if (childs.size() == 0) {
                if (text == "-") {
                    return MenuKind::Separator;
                } else {
                    return MenuKind::Item;
                }
            } else {
                return MenuKind::Menu;
            }
        }
    };

    struct Window {
        std::string windowClass;
        std::string class_;
        std::string name;
        std::string text;
        std::string rect;
        std::string style;
        std::string exStyle;
        std::list<Window> childs;
    };

    struct Frame : public Window {
        AcceleratorTable acceleratorTable;
        Menu menu;
    };

    class Parser {
    public:
        virtual ~Parser();
        virtual Frame parse() = 0;
    };
}

#endif
