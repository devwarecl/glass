
#pragma once 

#include "Widget.hpp"

#include <optional>

namespace wcl::core {
    class ComboBox : public Widget {
    public:
        ComboBox();

        ~ComboBox();

        size_t getItemCount() const;

        //std::string getItem(const size_t index) const;

        //void setItem(const size_t index, const std::string &value);

        void addItem(const std::string &value);

        void removeItem(const size_t index);

        std::optional<size_t> getSelectedIndex() const;

        void clear();
    };
}
