#include <winconw/basic_widgets/time_widget.hpp>
#include <chrono>
#include <ctime>

namespace wcw
{
    void time_widget::update()
    {
        _content_changed = true;
        autosize();
        fill_background();

        using clock = std::chrono::system_clock;
        auto now = clock::now();
        auto time = clock::to_time_t(now);
        auto tam = std::localtime(&time);
        char buff[64];
        std::strftime(buff, 64, "%A %c", tam);
        write_at(std::string(buff), 0, 0);

        update_children();
    }
}