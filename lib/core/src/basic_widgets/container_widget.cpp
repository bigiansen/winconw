#include <winconw/basic_widgets/container_widget.hpp>
#include <winconw/console.hpp>

namespace wcw
{
    void container_widget::update()
    {
        autosize();
        fill_background();
        update_children();
    }

    void container_widget::draw()
    {
        if(_console->size_changed())
        {
            widget::draw();
        }
        draw_children();
    }
}