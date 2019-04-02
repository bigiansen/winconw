#pragma once

#include <winconw/rect.hpp>
#include <winconw/con_char.hpp>
#include <string>
#include <vector>

namespace wcw
{
    /* >> fwd */
    class console; 

    class widget
    {
    protected:
        rect _bounds_rect;
        console* _console_ptr;
        std::vector<std::vector<con_char>> _char_rows;

    public:
        widget() = delete;
        widget(console* con_ptr, rect bounds_rect);

        rect bounding_rect() const noexcept;

        void set_position(int x, int y) noexcept;
        void set_size(int w, int h) noexcept;
        void set_bounds(rect bounds_rect) noexcept;

        virtual void draw();
        virtual void update() = 0;
    };
}
