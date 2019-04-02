#pragma once

#include <winconw/color.hpp>
#include <vector>

namespace wcw
{
    struct console_char
    {
        char character;
        color foreground_color;
        color background_color;

        constexpr console_char()
            : character('\0')
            , background_color(color::BLACK)
            , foreground_color(color::WHITE)
        { }

        constexpr console_char(char ch, color fcol, color bcol)
            : character(ch)
            , background_color(bcol)
            , foreground_color(fcol)
        { }

        operator CHAR_INFO()
        {
            CHAR_INFO result = {};
            result.Char.AsciiChar = character;
            result.Attributes = get_char_info_attr(foreground_color, background_color);
            return result;
        }

        static std::vector<console_char> text2vec(
            const std::string& text, 
            color fcol, 
            color bcol);
    };
}