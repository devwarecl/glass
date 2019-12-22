
#pragma once

#ifndef __wcl_gen_menu_hpp__
#define __wcl_gen_menu_hpp__

#include <memory>
#include <algorithm>
#include <wcl/Menu.hpp>
#include <wcl/AcceleratorTable.hpp>

namespace wcl { namespace gen {
    
    struct Menu {
        int id = 0;
        std::wstring text;
        std::vector<Menu> entries;
        
        Menu(int id_, const std::wstring &text_);
        Menu(int id_, const std::wstring &text_, const Menu &menu);
        Menu(int id_, const std::wstring &text_, const std::vector<Menu> &entries);
        
        Menu(const std::wstring &text_, const Menu &menu);
        Menu(const std::wstring &text_, const std::vector<Menu> &entries);
        
        Menu(const std::vector<Menu> &entries);
        
        std::unique_ptr<wcl::Menu> Generate(const std::vector<Accelerator> &accelerators = std::vector<Accelerator>()) const;
    };
    
    inline Menu::Menu(int id_, const std::wstring &text_) : id(id_), text(text_) {}

    inline Menu::Menu(int id_, const std::wstring &text_, const Menu &menu) : id(id_), text(text_) {
        entries.push_back(menu);
    }

    inline Menu::Menu(int id_, const std::wstring &text_, const std::vector<Menu> &entries) : id(id_), text(text_), entries(std::move(entries)) {}

    inline Menu::Menu(const std::wstring &text_, const Menu &menu) : text(text_) {
        entries.push_back(menu);
    }

    inline Menu::Menu(const std::wstring &text_, const std::vector<Menu> &entries) : text(text_), entries(std::move(entries)) {}
    
    inline Menu::Menu(const std::vector<Menu> &entries) : entries(std::move(entries)) {}
    
    inline std::unique_ptr<wcl::Menu> Menu::Generate(const std::vector<Accelerator> &accelerators) const {
        auto menu = std::make_unique<wcl::Menu>();
        menu->Create();
        
        for (const auto& entry : this->entries) {
            std::wstring menuText = entry.text;

            auto accelerator = std::find_if (accelerators.begin(), accelerators.end(), [entry](const Accelerator &accel) {
                return entry.id == accel.cmd;
            });

            if (accelerator != accelerators.end()) {
                menuText += L"\t" + accelerator->ToString();
            }

            if (entry.entries.size() == 0) {
                if (entry.text == L"-") {
                    // separator
                    DWORD dwFlags = MF_ENABLED | MF_STRING | MF_SEPARATOR;
                    menu->Append(dwFlags, entry.id, L"");
                } else {
                    // menu item
                    DWORD dwFlags = MF_ENABLED | MF_STRING;
                    menu->Append(dwFlags, entry.id, menuText);    
                }
                
            } else {
                // menu with other menues
                DWORD dwFlags = MF_ENABLED | MF_STRING | MF_POPUP;
                
                menu->Append(dwFlags, entry.Generate(accelerators), menuText);
            }
        }
        
        return menu;
    }
}}

#endif
