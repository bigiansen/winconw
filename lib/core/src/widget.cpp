#include <winconw/widget.hpp>
#include <winconw/console.hpp>

namespace wcw
{
    widget::widget(console* con_ptr, rect bounds_rect)
    {
        _console_ptr = con_ptr;
        _bounds_rect = bounds_rect;
    }

    rect widget::bounding_rect() const noexcept
    {
        return _bounds_rect;
    }

    void widget::set_position(int x, int y) noexcept
    {
        _bounds_rect.x = x;
        _bounds_rect.y = y;
    }

    void widget::set_size(int w, int h) noexcept
    {
        _bounds_rect.w = w;
        _bounds_rect.h = h;
    }

    void widget::set_bounds(rect bounds_rect) noexcept
    {
        _bounds_rect = bounds_rect;
    }

    void widget::draw()
    {
        for(size_t i = 0; i < _bounds_rect.y; ++i)
        {
            _console_ptr->set_cursor_pos(_bounds_rect.x, _bounds_rect.y + i);
            std::vector<con_char>& row = _char_rows[i];
            if(row.size() > _bounds_rect.x)
            {
                std::vector<con_char> aux_clamped;
                aux_clamped.reserve(_bounds_rect.x);
                std::copy(row.begin(), row.end(), std::back_inserter(aux_clamped));
                _console_ptr->output(aux_clamped);
            }
            else
            {
                _console_ptr->output(row);
            }
        }
    }
}