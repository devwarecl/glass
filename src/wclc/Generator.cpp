
#include "Generator.hpp"
#include "HeaderTemplate.hpp"
#include "SourceTemplate.hpp"

#include <boost/algorithm/string.hpp>

namespace wclc {

    std::string GenerateFrameHeader(const Frame &frame) {
        std::string header = wclc::header_template;

        boost::replace_all(header, "${namespace}", "wcl");
        boost::replace_all(header, "${class}", frame.class_);

        // Menu
        std::string header_menu = "";
        std::string member_menu = "";

        if (frame.menu.childs.size()) {
            header_menu = "#include <wcl/Menu.hpp>";
            member_menu = "wcl::Menu menu;";
        }

        boost::replace_all(header, "${header_menu}", header_menu);
        boost::replace_all(header, "${member_menu}", member_menu);

        // AcceleratorTable
        std::string header_accelerators = "";
        std::string member_accelerators = "";

        if (frame.acceleratorTable.accelerators.size()) {
            header_accelerators = "#include <wcl/AcceleratorTable.hpp>";
            member_accelerators = "wcl::AcceleratorTable acceleratorTable;";
        }

        boost::replace_all(header, "${header_accelerators}", header_accelerators);
        boost::replace_all(header, "${member_accelerators}", member_accelerators);

        // Child Windows
        std::string member_childs;
        std::string header_members;

        for (const Window &child : frame.childs) {
            if (child.class_ != "") {
                member_childs += "wcl::" + child.class_ + " " + child.name + ";\n";
                header_members += "#include <wcl/" + child.class_ + ".hpp>\n";
            } else {
                member_childs += "wcl::Window" + child.name + ";\n";
            }
        }

        boost::replace_all(header, "${member_childs}", member_childs);
        boost::replace_all(header, "${header_members}", header_members);

        return header;
    }

    std::list<std::string> GenerateCommandEnumImpl(const Menu &menu) {
        std::list<std::string> command_enum_list;

        if (menu.command != "") {
            command_enum_list.push_back(menu.command);
        }

        for (Menu childMenu : menu.childs) {
            command_enum_list.merge(GenerateCommandEnumImpl(childMenu));
        }

        return command_enum_list;
    }

    std::string GenerateCommandEnum(const Frame &frame) {

        const std::string separator = ", \n";

        std::string command_enum;
        std::list<std::string> command_enum_list = GenerateCommandEnumImpl(frame.menu);

        if (command_enum_list.size()) {
            command_enum_list.begin()->append("=1000");

            command_enum 
                = "enum {\n" 
                + boost::join(command_enum_list, separator) 
                + "\n};\n";
        }

        return command_enum;
    }

    std::string GenerateMenuSeparator() {
        return "{0, L\"-\"}";
    }

    std::string GenerateMenuItem(const Menu &menu) {
        return "{" + menu.command + ", L\"" + menu.text + "\"}";
    }

    std::string GenerateMenu(const Menu &menu) {
        std::string menu_data = "";

        menu_data += "{L\"" + menu.text + "\", {";

        int i = 0;

        for (const Menu &child : menu.childs) {
            switch (child.GetKind()) {
                case MenuKind::Separator:    
                    menu_data += GenerateMenuSeparator(); 
                    break;

                case MenuKind::Item:        
                    menu_data += GenerateMenuItem(child); 
                    break;

                case MenuKind::Menu:        
                    menu_data += GenerateMenu(child); 
                    break;
            }

            if (++i < static_cast<int>(menu.childs.size())) {
                menu_data += ", ";
            }
        }

        menu_data += "}}";

        return menu_data;
    }

    std::string GenerateMenuBar(const Menu &menu) {
        std::string menu_data = "wcl::gen::Menu menuGen = " + GenerateMenu(menu) + ";";
        std::string menu_gen = "        this->SetMenu(std::move(menuGen.Generate()));";

        return menu_data + "\r\n" + menu_gen;
    }

    std::string GenerateFrameSource(const Frame &frame) {
        std::string source = wclc::source_template;

        boost::replace_all(source, "${namespace}", "wcl");
        boost::replace_all(source, "${class}", frame.class_);
        boost::replace_all(source, "${window_class}", frame.windowClass);

        // generate command enumeration
        std::string command_enum = GenerateCommandEnum(frame);
        boost::replace_all(source, "${command_enum}", command_enum);

        // generate menu
        boost::replace_all(source, "${construction_menu}", GenerateMenuBar(frame.menu));

        return source;
    }
    
    Generator::Generator() {}

    void Generator::setFrame(const Frame &frame) {
        this->frame = frame;
    }

    Generator::~Generator() {}

    std::string Generator::generateHeader() {
        return GenerateFrameHeader(frame);
    }

    std::string Generator::generateSource() {
        return GenerateFrameSource(frame);
    }
}
