
#pragma once

#ifndef __wcl_menu_hpp__
#define __wcl_menu_hpp__

#include <string>
#include <memory>
#include <list>

namespace wcl {

    struct MenuHandle {
        HMENU hMenu = NULL;
    
        explicit MenuHandle(HMENU hMenu);

        MenuHandle();
        MenuHandle(MenuHandle &&other);
        ~MenuHandle();
    
        MenuHandle& operator=(MenuHandle &&other);
    
        operator HMENU();
    
        void Create();
        void Destroy();
    
        MenuHandle(const MenuHandle&) = delete;
        MenuHandle& operator=(const MenuHandle&) = delete;
    };
}

namespace wcl {
    
    class Menu;
    typedef std::unique_ptr<Menu> MenuPtr;
    
    class Menu {
    public:
        Menu();
        ~Menu();

        Menu(Menu &&other);

        Menu& operator= (Menu &&other);

        operator HMENU();
        
        HMENU GetHandle() const;
        
        void Create();
    
        void Destroy();

        void Append(UINT uFlags, UINT idNewItem, const std::wstring &newItem);
        
        void Append(UINT uFlags, MenuPtr menu, const std::wstring &newItem);

    public:
        Menu(const Menu &other) = delete;
        Menu& operator=(const Menu &other) = delete;

    private:
        std::list<MenuPtr> MenuList;
        MenuHandle Handle;
    };
}
    
namespace wcl {
    inline MenuHandle::MenuHandle() {}
    
    inline MenuHandle::MenuHandle(HMENU hMenu) {
        this->hMenu = hMenu;
    }
    
    inline MenuHandle::~MenuHandle() {
        this->Destroy();
    }
    
    inline MenuHandle::MenuHandle(MenuHandle &&other) {
        this->hMenu = other.hMenu;
        other.hMenu = NULL;
    }
    
    inline MenuHandle& MenuHandle::operator=(MenuHandle &&other) {
        this->Destroy();
        
        this->hMenu = other.hMenu;
        other.hMenu = NULL;
        
        return *this;
    }
    
    inline MenuHandle::operator HMENU() {
        assert(this->hMenu);
        
        return this->hMenu;
    }
    
    inline void MenuHandle::Create() {
        this->hMenu = ::CreateMenu();
    }
    
    inline void MenuHandle::Destroy() {
        if (!this->hMenu) {
            ::DestroyMenu(this->hMenu);
            this->hMenu = NULL;
        }
    }
}

namespace wcl {
    inline Menu::Menu() {}
    inline Menu::~Menu() {}

    inline Menu::Menu(Menu &&other) {
        this->MenuList = std::move(other.MenuList);
        this->Handle = std::move(other.Handle);
    }

    inline Menu& Menu::operator= (Menu &&other) {
        this->MenuList = std::move(other.MenuList);
        this->Handle = std::move(other.Handle);
        
        return *this;
    }

    inline Menu::operator HMENU() {
        return this->Handle;
    }

    inline void Menu::Create() {
        this->Handle.Create();
    }
    
    inline void Menu::Destroy() {
        this->MenuList.clear();
        this->Handle.Destroy();
    }

    inline void Menu::Append(UINT uFlags, UINT idNewItem, const std::wstring &newItem) {
        if (!::AppendMenuW(this->Handle, uFlags, (UINT_PTR)idNewItem, newItem.c_str())) {
            throw wcl::Exception("Couldn't add a menu item.");
        }
    }

    inline void Menu::Append(UINT uFlags, MenuPtr menu, const std::wstring &newItem) {
        HMENU hMenu = (HMENU) menu->Handle;

        if (!::AppendMenuW(this->Handle, uFlags, (UINT_PTR)hMenu, newItem.c_str())) {
            throw wcl::Exception("Couldn't add a submenu.");
        }

        MenuList.push_back(std::move(menu));
    }
    
    inline HMENU Menu::GetHandle() const {
        return this->Handle.hMenu;
    }
}

#endif
