
#pragma once 

#include "AbstractWindow.hpp"
#include "CustomWindow.hpp"
#include "MessageLoop.hpp"
#include "Window.hpp"
#include "WindowClassRegistry.hpp"

namespace glass {
    class Button : public Window {
    public:
        Button() : Window("BUTTON", WS_CHILD | WS_VISIBLE, NULL) {}
    };

    class Label : public Window {
    public:
        Label() : Window("STATIC", WS_CHILD | WS_VISIBLE, NULL) {}
    };
    
    class TextBox : public Window {
    public:
        TextBox() : Window("EDIT", WS_CHILD | WS_VISIBLE, NULL) {}
    };

    class CheckBox : public Window {
    public:
        enum STATE {
            UNCHECKED,
            CHECKED, 
            GRAYED
        };

        CheckBox() : Window("BUTTON", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX, NULL) {}

        void setState(const STATE value) {
            WPARAM state = 0;

            switch (value) {
                case CHECKED: state = BST_CHECKED; break;
                case UNCHECKED: state = BST_UNCHECKED; break;
                case GRAYED: state = BST_INDETERMINATE; break;
            }

            sendMessage(BM_SETCHECK, state);
        }

        STATE getState() const {
            LRESULT state = sendMessage(BM_GETCHECK);

            assert(state == BST_CHECKED || state == BST_UNCHECKED || state == BST_INDETERMINATE);

            switch (state) {
                case BST_CHECKED: return CHECKED;
                case BST_UNCHECKED: return UNCHECKED;
                case BST_INDETERMINATE: return GRAYED;
            }
        }
    };

    class RadioButton : public Window {
    public:
        RadioButton() : Window("BUTTON", WS_CHILD | WS_VISIBLE | BS_AUTORADIOBUTTON, NULL) {}

        void setState(const bool value) {
            sendMessage(BM_SETCHECK, value ? BST_CHECKED : BST_UNCHECKED);
        }

        bool getState() const {
            LRESULT state = sendMessage(BM_GETCHECK);

            assert(state == BST_CHECKED || state == BST_UNCHECKED);

            return state == BST_CHECKED ? true : false;
        }
    };
    
    class GroupBox : public Window {
    public:
        GroupBox() : Window("BUTTON", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, NULL) {}
    };

    class ListBox : public Window {
    public:
        ListBox() : Window("BUTTON", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, NULL) {}
    };
    
    class ComboBox : public Window {
    public:
        ComboBox () : Window("COMBOBOX", WS_CHILD | WS_VISIBLE | BS_GROUPBOX, NULL) {}
    };
}
