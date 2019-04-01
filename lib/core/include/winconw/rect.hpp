#pragma once

#include <winconw/defs.hpp>

#include <Windows.h>
#include <algorithm>
#include <limits>

namespace wcw
{
    struct rect
    {
        int x = 0;
        int y = 0;
        int w = 0;
        int h = 0;

        constexpr rect() noexcept {}
        
        constexpr rect(int x, int y, int w, int h) noexcept
        {
            this->x = x;
            this->y = y;
            this->w = w;
            this->h = h;
        }

        constexpr COORD size_coord() const
        {
            COORD result = {};
            result.X = static_cast<SHORT>(w);
            result.Y = static_cast<SHORT>(h);
            return result;
        }

        constexpr operator RECT() const
        {
            RECT result = {};
            result.bottom = y + h - 1;
            result.left = x;
            result.right = x + w - 1;
            result.top = y;
            return result;
        }

        constexpr operator SMALL_RECT() const
        {
            auto max_short = [](int v) constexpr -> SHORT
            {
                return static_cast<SHORT>(
                    std::min(v, static_cast<int>(std::numeric_limits<SHORT>::max()))
                );
            };

            SMALL_RECT result = {};
            result.Bottom = max_short(y + h - 1);
            result.Left = max_short(x);
            result.Right = max_short(x + w -1);
            result.Top = max_short(y);
            return result;
        }
    };
}