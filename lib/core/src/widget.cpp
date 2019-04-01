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
        // TODO
    }
}