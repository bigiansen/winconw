#include <winconw/basic_widgets/lineview_widget.hpp>

namespace wcw
{
    void lineview_widget::add_line(const std::string& text)
    {
        int largest_index = (*_lines.rbegin()).first;
        _lines.emplace(largest_index + 1, text);
    }

    void lineview_widget::add_line(std::string&& text)
    {
        int largest_index = (*_lines.rbegin()).first;
        _lines.emplace(largest_index + 1, std::move(text));
    }

    void lineview_widget::set_line(int index, const std::string& text)
    {
        if(_lines.count(index) > 0)
        {
            _lines[index] = text;
        }
        else
        {
            _lines.emplace(index, text);
        }        
    }

    void lineview_widget::set_line(int index, std::string&& text)
    {
        if(_lines.count(index) > 0)
        {
            _lines[index] = std::move(text);
        }
        else
        {
            _lines.emplace(index, std::move(text));
        }
    }

    void lineview_widget::clear_lines()
    {
        _lines.clear();
        fill_background();
    }

    int lineview_widget::offset() const noexcept
    {
        return _vertical_offset;
    }

    void lineview_widget::set_offset(int offset)
    {
        _vertical_offset = offset;
    }

    void lineview_widget::update()
    {        
        for(int i = 0; i < _transform.h; ++i)
        {
            if(_lines.count(_vertical_offset + i) == 0)
            {
                write_at(std::string(_transform.w, ' '), 0, i);
            }
            else
            {
                const std::string& lstr = _lines[_vertical_offset + i];
                if(lstr.size() > static_cast<size_t>(_transform.w))
                {
                    std::string aux = lstr.substr(0, _transform.w);
                    write_at(aux, 0, i);
                }
                else
                {
                    std::string aux = lstr + std::string(_transform.w - lstr.size(), ' ');
                    write_at(aux, 0, i);
                }
            }            
        }
        update_children();
    }
}