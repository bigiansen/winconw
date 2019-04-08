#pragma once

#include <winconw/rect.hpp>
#include <winconw/console_char.hpp>
#include <winconw/autosize_info.hpp>
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
        std::vector<std::unique_ptr<widget>> _children;

        color _current_fcol = color::WHITE;
        color _current_bcol = color::BLACK;

        std::map<int, std::vector<console_char>> _char_rows;

        bool _content_changed = true;

        bool _autosize = false;
        autosize_info _autosize_info;

    public:
        widget() = delete;
        widget(console* con_ptr, rect bounds_rect, widget* parent = nullptr);

        template<typename T>
        T* add_child(console* con_ptr, rect bounds)
        {
            _children.push_back(std::make_unique<T>(con_ptr, bounds, this));
            return dynamic_cast<T*>(_children.back().get());
        }

        rect bounding_rect() const noexcept;

        void set_position(int x, int y) noexcept;
        void set_size(int w, int h) noexcept;
        void set_bounds(rect bounds_rect) noexcept;

        void enable_autosize(autosize_info info);

        void set_current_color(color fcol, color bcol);
        void set_current_text_color(color fcol);
        void set_current_back_color(color bcol);

        bool is_root() const noexcept;

        void inherit_background();
        void inherit_foreground();
        void inherit_colors();

        void fill_area(rect area, char ch);
        void fill_background();

        virtual void get_absolute_position(int& xres, int& yres);

        virtual void write_at(const std::string& text, int x, int y);
        virtual void write_at(console_char ch, int x, int y);
        void clear_row(int row_index);
        void clear_rows();

        virtual void draw();
        virtual void update() = 0;

    protected:
        virtual void autosize();
        virtual void update_children();
        virtual void draw_children();
    };
}
