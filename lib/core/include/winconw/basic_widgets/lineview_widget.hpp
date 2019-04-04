#pragma once

#include <winconw/widget.hpp>
#include <map>
#include <string>

namespace wcw
{
    class lineview_widget : public widget
    {
    protected:
        std::map<int, std::string> _lines;
        int _vertical_offset = 0;
        bool _needs_recreate = true;

    public:
        lineview_widget(console* con_ptr, rect bounds, widget* parent)
            : widget(con_ptr, bounds, parent)
        { }

        void add_line(const std::string& text);
        void add_line(std::string&& text);

        void set_line(int index, const std::string& text);
        void set_line(int index, std::string&& text);

        void clear_lines();

        int offset() const noexcept;
        void set_offset(int offset);

        void update() override;
    };
}