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

    void widget::update_children()
    {
        for(auto& child : _children)
        {
            child->update();
        }
    }

    rect widget::bounding_rect() const noexcept
    {
        return _transform;
    }

    void widget::set_position(int x, int y) noexcept
    {
        _content_changed = true;
        _transform.x = x;
        _transform.y = y;
    }

    void widget::set_size(int w, int h) noexcept
    {
        _content_changed = true;
        _transform.w = w;
        _transform.h = h;
    }

    void widget::set_bounds(rect bounds_rect) noexcept
    {
        _content_changed = true;
        _transform = bounds_rect;
    }

    void widget::enable_autosize(autosize_info info)
    {
        _content_changed = true;
        _autosize = true;
        _autosize_info = info;
    }

    void widget::set_current_color(color fcol, color bcol)
    {
        _content_changed = true;
        _current_fcol = fcol;
        _current_bcol = bcol;
    }
    
    void widget::set_current_text_color(color fcol)
    {
        _content_changed = true;
        _current_fcol = fcol;
    }

    void widget::set_current_back_color(color bcol)
    {
        _content_changed = true;
        _current_bcol = bcol;
    }

    bool widget::is_root() const noexcept
    {
        return _parent == nullptr;
    }

    void widget::fill_area(rect area, char ch)
    {
        _content_changed = true;
        std::string text_line(area.w, ch);
        for(int y = 0; y < area.h; ++y)
        {
            int ypos = area.y + y;
            for(int x = 0; x < area.w; ++x)
            {
                int xpos = area.x + x;
                write_at(text_line, xpos, ypos);
            }
        }
    }

    void widget::fill_background()
    {
        _content_changed = true;
        for(int i = 0; i < _transform.h; ++i)
        {
            write_at(std::string(_transform.w, ' '), 0, i);
        }
    }
    
    void widget::write_at(const std::string& text, int x, int y)
    {
        _content_changed = true;
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

    void widget::write_at(console_char ch, int x, int y)
    {
        _content_changed = true;
        if(_char_rows.count(y) != 0)
        {
            _char_rows.emplace(y, std::vector<console_char>());
        }
        std::vector<console_char>& row = _char_rows[y];
        row[x] = ch;
    }

    void widget::inherit_background()
    {
        _content_changed = true;
        if(!is_root())
        {
            _current_bcol = _parent->_current_bcol;
        }
    }

    void widget::inherit_foreground()
    {
        _content_changed = true;
        if(!is_root())
        {
            _current_fcol = _parent->_current_fcol;
        }
    }

    void widget::inherit_colors()
    {
        _content_changed = true;
        if(!is_root())
        {
            _current_fcol = _parent->_current_fcol;
            _current_bcol = _parent->_current_bcol;
        }
    }

    void widget::clear_row(int row_index)
    {
        _content_changed = true;
        if(_char_rows.count(row_index) != 0)
        {
            _char_rows[row_index].clear();
        }
    }

    void widget::clear_rows()
    {
        _content_changed = true;
        _char_rows.clear();
    }

    void widget::get_absolute_position(int& xres, int& yres)
    {
        if(is_root())
        {
            xres = _transform.x;
            yres = _transform.y;
            return;
        }

        int x = _transform.x;
        int y = _transform.y;

        widget* current = this;
        
        while(!current->is_root())
        {
            current = current->_parent;
            x += current->_transform.x;
            y += current->_transform.y;
        }

        xres = x;
        yres = y;
    }

    void widget::draw_children()
    {
        for(auto& child : _children)
        {
            child->draw();
        }
    }

    void widget::draw()
    {
        if(_content_changed)
        {
            int abs_offset_x, abs_offset_y;
            get_absolute_position(abs_offset_x, abs_offset_y);

            for(size_t i = 0; i < static_cast<size_t>(_transform.h); ++i)
            {
                _console->set_cursor_pos(abs_offset_x, abs_offset_y + i);
                std::vector<console_char>& row = _char_rows[i];
                if(row.size() > static_cast<size_t>(_transform.w))
                {
                    std::vector<console_char> aux_clamped;
                    std::copy(row.begin(), row.begin() + _transform.w, std::back_inserter(aux_clamped));
                    _console->output(aux_clamped);
                }
                else
                {
                    _console->output(row);
                }
            }
        }
        draw_children();
        _content_changed = false;
    }

    void widget::autosize()
    {
        if(_autosize && _console->size_changed())
        {
            rect parent_tform = is_root() ? _console->get_size() : _parent->_transform ;
            rect result_tform = _transform;
            if(_autosize_info.left)
            {
                result_tform.w = 0;
                result_tform.x -= (_transform.x - _autosize_info.pad_left);
                result_tform.w += _transform.x;
            }
            if(_autosize_info.right)
            {
                if(!_autosize_info.left) { result_tform.w = 0; }
                result_tform.w += (((parent_tform.w) - _transform.x) - _autosize_info.pad_right);
            }
            if(_autosize_info.top)
            {
                result_tform.h = 0;
                result_tform.y -= (_transform.y - _autosize_info.pad_top);
                result_tform.h += _transform.y;
            }
            if(_autosize_info.bottom)
            {
                if(!_autosize_info.top) { result_tform.h = 0; }
                result_tform.h += (((parent_tform.h) - _transform.y) - _autosize_info.pad_bottom);
            }
            
            _transform = result_tform;
        }
    }
}