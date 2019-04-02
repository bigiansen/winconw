#pragma once

#include <winconw/rect.hpp>
#include <winconw/console_char.hpp>
#include <string>
#include <vector>

namespace wcw
{
    /* >> fwd */
    class console; 

    class widget
    {
    protected:
        rect _transform;

        console* _console = nullptr;
        widget* _parent = nullptr;

        color _current_fcol = color::WHITE;
        color _current_bcol = color::BLACK;

        std::map<int, std::vector<console_char>> _char_rows;

    public:
        widget() = delete;
        widget(console* con_ptr, rect bounds_rect, widget* parent = nullptr);

        rect bounding_rect() const noexcept;

        void set_position(int x, int y) noexcept;
        void set_size(int w, int h) noexcept;
        void set_bounds(rect bounds_rect) noexcept;

        void set_current_color(color fcol, color bcol);
        void set_current_text_color(color fcol);
        void set_current_back_color(color bcol);

        bool is_root() const noexcept;

        void write_at(const std::string& text, int x, int y);
        void clear_row(int row_index);

        virtual void draw();
        virtual void update() = 0;
    };
}
