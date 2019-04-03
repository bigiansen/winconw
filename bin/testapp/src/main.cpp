#include <winconw/widget.hpp>
#include <winconw/console.hpp>
#include <winconw/basic_widgets.hpp>

#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>

class container_widget : public wcw::widget
{
public:
    container_widget(wcw::console* con_ptr, wcw::rect bounds_rect)
        : widget(con_ptr, bounds_rect)
    { }

    void update() override
    { 
        update_children();
    }
};

int main()
{
    wcw::console con;
    con.initialize(wcw::rect(0, 0, 40, 20));
    wcw::rect bounds(1, 1, 16, 1);
    container_widget cont(&con, wcw::rect(0, 0, 0, 0));
    cont.add_child(std::make_unique<wcw::time_widget>(&con, bounds));
    while(true)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
        cont.update();
        cont.draw();
    }
    int i = 0;
    std::cin >> i;
    return 0;
}