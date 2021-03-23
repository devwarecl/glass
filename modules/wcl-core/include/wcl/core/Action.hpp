
#pragma once 

#include <string>

namespace wcl::core {
    class Action {
    public:
        Action* setText(const std::string &text);

        Action* setShortcut(const std::string &shortcut);

        int getId() const;

        std::wstring getText() const;

        std::wstring getShortcut() const;

    private:

    };
}
