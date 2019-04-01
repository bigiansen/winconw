#pragma once

#include <vector>
#include <winconw/con_char.hpp>

namespace wcw
{
    struct widget_content
    {
        std::vector<std::vector<con_char>> char_rows;
    };
}