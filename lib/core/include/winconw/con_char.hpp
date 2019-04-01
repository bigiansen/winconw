#pragma once

#include <winconw/color.hpp>

namespace wcw
{
    struct con_char
    {
        char character;
        color foreground_color;
        color background_color;

        constexpr con_char(char ch, color fcol, color bcol)
            : character(ch)
            , background_color(bcol)
            , foreground_color(fcol)
        { }

        constexpr operator CHAR_INFO()
        {
            CHAR_INFO result = {};
            result.Char.AsciiChar = character;
            result.Attributes = get_char_info_attr(foreground_color, background_color);
        }
    };
}