#include <winconw/basic_widgets/container_widget.hpp>

namespace wcw
{
    void container_widget::update()
    {
        update_children();
    }

    void container_widget::draw()
    {
        draw_children();
    }
}