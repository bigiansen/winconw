#include <winconw/console.hpp>

namespace wcw
{
    void console::initialize(rect win_rect)
    {
        _proc_handle = GetCurrentProcess();        
        _con_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        set_console_size(win_rect);
        CONSOLE_FONT_INFOEX cfont_info;
        cfont_info.cbSize = sizeof(CONSOLE_FONT_INFOEX);
        cfont_info.dwFontSize = COORD{16,0};
        cfont_info.FontWeight = FW_NORMAL;
        wcscpy_s(cfont_info.FaceName, 12, L"FixedSys");
        SetCurrentConsoleFontEx(_con_handle, TRUE, &cfont_info);
    }

    void console::set_console_size(rect win_rect)
    {
        SMALL_RECT rect = win_rect;
        SetConsoleWindowInfo(_con_handle, TRUE, &rect);
        SetConsoleScreenBufferSize(_con_handle, win_rect.size_coord());
        SetConsoleWindowInfo(_con_handle, TRUE, &rect);
        SetConsoleScreenBufferSize(_con_handle, win_rect.size_coord());
    }

    void console::allocate_console()
    {
        if(GetConsoleWindow() == NULL && AllocConsole() == FALSE)
        {
            throw std::runtime_error("Unable to allocate console for process");
        }
        _con_handle = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(_con_handle, &_con_info);
    }

    void console::set_text_color(color col)
    {
        _text_color = col;
        update_console_colors();
    }

    void console::set_background_color(color col)
    {
        _back_color = col;
        update_console_colors();
    }
    
    void console::set_cursor_pos(int x, int y)
    {
        SetCursorPos(x, y);
    }

    void console::write(const std::string& text)
    {
        DWORD chars_written = 0;
        if(WriteConsoleA(_con_handle, text.c_str(), text.length(), &chars_written, NULL) == FALSE)
        {
            throw std::runtime_error("Error while attempting to write to console");
        }
    }

    void console::write(const std::u16string& text)
    {
        DWORD chars_written = 0;
        if(WriteConsoleW(_con_handle, text.c_str(), text.length(), &chars_written, NULL) == FALSE)
        {
            throw std::runtime_error("Error while attempting to write to console");
        }
    }

    void console::write_at(char ch, int x, int y)
    {
        set_cursor_pos(x, y);
        write(std::string(1, ch));
    }

    void console::write_at(char16_t ch, int x, int y)
    {
        set_cursor_pos(x, y);
        write(std::u16string(1, ch));
    }

    void console::clear()
    {
        WORD attr = get_char_info_attr(_text_color, _back_color);
        DWORD char_count = _con_info.dwSize.X * _con_info.dwSize.Y;
        COORD zero_coord;
        zero_coord.X = 0;
        zero_coord.Y = 0;
        DWORD chars_written = 0;
        FillConsoleOutputAttribute(_con_handle, attr, char_count, zero_coord, &chars_written);
        FillConsoleOutputCharacterA(_con_handle, ' ', char_count, zero_coord, &chars_written);
    }

    void console::update_console_colors()
    {
        WORD attr = get_char_info_attr(_text_color, _back_color);
        SetConsoleTextAttribute(_con_handle, attr);
    }

    CHAR_INFO console::get_char_info(CHAR ach)
    {
        CHAR_INFO result;
        result.Attributes = get_char_info_attr(_text_color, _back_color);
        result.Char.AsciiChar = ach;
        return result;
    }

    CHAR_INFO console::get_char_info(WCHAR uch)
    {
        CHAR_INFO result;
        result.Attributes = get_char_info_attr(_text_color, _back_color);
        result.Char.UnicodeChar = uch;
        return result;
    }    
}