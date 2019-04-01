#pragma once

#include <winconw/defs.hpp>

#include <Windows.h>
#include <map>

namespace wcw
{
    enum class color
    {
        BLACK,
        WHITE,
        RED,
        GREEN,
        BLUE,
        YELLOW,
        MAGENTA,
        GRAY,
        CYAN,
        DARK_RED,
        DARK_GREEN,
        DARK_BLUE,
        DARK_YELLOW,
        DARK_MAGENTA,
        DARK_GRAY,
        DARK_CYAN
    };

    extern WORD get_char_info_attr(color fcol, color bcol);
}
