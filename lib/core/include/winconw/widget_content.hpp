#pragma once

#include <vector>
#include <winconw/console_char.hpp>

namespace wcw
{
    struct widget_content
    {
        std::vector<std::vector<console_char>> char_rows;
    };
}