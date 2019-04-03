#pragma once

#include <winconw/widget.hpp>

namespace wcw
{
    class time_widget : public widget
    {
    public:
        time_widget(console* con_ptr, rect size, widget* parent = nullptr)
            : widget(con_ptr, size, parent)
        { }

        void update() final;
    };
}