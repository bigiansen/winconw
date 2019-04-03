#pragma once

#include <winconw/widget.hpp>

namespace wcw
{
    class container_widget : public widget
    {
    public:
        container_widget(console* con_ptr, rect size, widget* parent = nullptr)
            : widget(con_ptr, size, parent)
        { }

        virtual void update() override;
    };
}