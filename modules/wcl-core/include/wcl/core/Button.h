
#pragma once 

#include "Widget.hpp"

#include <functional>
#include <map>

namespace wcl::core {
    class Button : public Widget {
    public:
        enum class Notifications {
            Clicked
        };

        bool create(const Rect &area, Widget *parent) override;

        void connect(Notifications notification, std::function<void ()> fn);

    public:
        Button();

    private:
        std::map<Notifications, std::function<void ()>> mConnections;
    };
}
