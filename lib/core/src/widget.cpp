#include <winconw/widget.hpp>
#include <winconw/console.hpp>

namespace wcw
{
    widget::widget(console* con_ptr, rect bounds_rect, widget* parent)
    {
        _console = con_ptr;
        _transform = bounds_rect;
        _parent = parent;
    }

    rect widget::bounding_rect() const noexcept
    {
        return _transform;
    }

    void widget::set_position(int x, int y) noexcept
    {
        _transform.x = x;
        _transform.y = y;
    }

    void widget::set_size(int w, int h) noexcept
    {
        _transform.w = w;
        _transform.h = h;
    }

    void widget::set_bounds(rect bounds_rect) noexcept
    {
        _transform = bounds_rect;
    }

    void widget::set_current_color(color fcol, color bcol)
    {
        _current_fcol = fcol;
        _current_bcol = bcol;
    }
    
    void widget::set_current_text_color(color fcol)
    {
        _current_fcol = fcol;
    }
    
    void widget::set_current_back_color(color bcol)
    {
        _current_bcol = bcol;
    }

    bool widget::is_root() const noexcept
    {
        return _parent == nullptr;
    }
    
    void widget::write_at(const std::string& text, int x, int y)
    {
        if(_char_rows.count(y) != 0)
        {
            _char_rows.emplace(y, std::vector<console_char>());
        }
        std::vector<console_char>& row = _char_rows[y];

        if(row.size() < (x + text.size()))
        {
            row.resize(x + text.size());
        }

        for(size_t i = 0; i < text.size(); ++i)
        {
            size_t index = x + i;
            row[index] = console_char(text[i], _current_fcol, _current_bcol);
        }
    }

    void widget::clear_row(int row_index)
    {
        if(_char_rows.count(row_index) != 0)
        {
            _char_rows[row_index].clear();
        }
    }

    void widget::draw()
    {
        // TODO: Apply parent transform
        for(size_t i = 0; i < static_cast<size_t>(_transform.y); ++i)
        {
            _console->set_cursor_pos(_transform.x, _transform.y + i);
            std::vector<console_char>& row = _char_rows[i];
            if(row.size() > static_cast<size_t>(_transform.x))
            {
                std::vector<console_char> aux_clamped;
                aux_clamped.reserve(_transform.x);
                std::copy(row.begin(), row.end(), std::back_inserter(aux_clamped));
                _console->output(aux_clamped);
            }
            else
            {
                _console->output(row);
            }
        }
    }
}