#pragma once

namespace wcw
{
    struct autosize_info
    {
        bool left = false;
        bool right = false;
        bool top = false;
        bool bottom = false;

        int pad_right = 0;
        int pad_left = 0;
        int pad_top = 0;
        int pad_bottom = 0;

        constexpr autosize_info() {}

        constexpr autosize_info(bool l, bool r, bool top, bool bottom)
        {
            left = l;
            right = r;
            this->top = top;
            this->bottom = bottom;
        }
    };
}