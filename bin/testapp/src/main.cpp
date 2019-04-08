#include <winconw/widget.hpp>
#include <winconw/console.hpp>
#include <winconw/basic_widgets.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>

int main()
{
    wcw::console con;
    con.initialize(wcw::rect(0, 0, 80, 40));
    wcw::lineview_widget* lw = con.add_widget<wcw::lineview_widget>(wcw::rect(10, 5, 0, 0));
    lw->set_current_back_color(wcw::color::GRAY);
    auto asz = wcw::autosize_info(false, true, false, true);
    asz.pad_right = 3;
    lw->enable_autosize(asz);
    lw->set_line(0, "HELLO");
    lw->set_line(1, " MY");
    lw->set_line(2, "  FREN");

    while(true)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(50ms);
        con.update();
        con.draw();
    }
    int i = 0;
    std::cin >> i;
    return 0;
}