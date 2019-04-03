#include <winconw/basic_widgets/container_widget.hpp>

namespace wcw
{
    void container_widget::update()
    {
        update_children();
    }
}