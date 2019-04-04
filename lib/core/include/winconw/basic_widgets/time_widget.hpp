#pragma once

#include <winconw/widget.hpp>

namespace wcw
{
    class time_widget : public widget
    {
    public:
        time_widget(console* con_ptr, rect size, widget* parent = nullptr)
            : widget(con_ptr, size, parent)
        { 
            _current_fcol = color::BLACK;
            _current_bcol = color::YELLOW;
        }

        void update() final;
    };
}