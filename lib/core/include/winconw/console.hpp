#pragma once

#include <winconw/defs.hpp>

#include <Windows.h>
#include <conio.h>
#include <stdexcept>
#include <vector>
#include <memory>

#include <winconw/color.hpp>
#include <winconw/rect.hpp>
#include <winconw/console_char.hpp>
#include <winconw/widget.hpp>
#include <winconw/basic_widgets/container_widget.hpp>

namespace wcw
{
    class console
    {
    private:
        HANDLE _proc_handle;
        HANDLE _con_handle;
        color _text_color;
        color _back_color;
        CONSOLE_SCREEN_BUFFER_INFO _con_info;
        std::unique_ptr<container_widget> _root_widget;
        bool _size_changed = false;
        bool _first_update = true;

    public:
        void initialize(rect win_rect, const std::wstring& fontName = L"FixedSys");

        template<typename T>
        T* add_widget(rect bounds)
        {
            return _root_widget->add_child<T>(this, bounds);
        }

        void set_text_color(color);
        void set_background_color(color);

        rect get_size();
        bool size_changed() const;

        void set_cursor_pos(int x, int y);

        void write(const std::string& text);
        void write(const std::u16string& text);

        void write_at(char ch, int x, int y);
        void write_at(char16_t ch, int x, int y);

        void output(const std::vector<console_char>& chars);
        widget* root_widget();

        void update();
        void draw();

        void clear();
        
    private:
        void disable_window_controls();
        void hide_cursor();
        void set_console_size(rect win_rect);
        void set_console_font(const std::wstring& fontName);
        void allocate_console();
        void update_console_colors();
        CHAR_INFO get_char_info(CHAR ach);
        CHAR_INFO get_char_info(WCHAR uch);
    };    
}