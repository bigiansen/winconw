#include <winconw/widget.hpp>
#include <winconw/console.hpp>
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

class time_widget : public wcw::widget
{
public:
    time_widget(wcw::console* con_ptr, wcw::rect bounds_rect)
        : widget(con_ptr, bounds_rect)
    {
        _current_bcol = wcw::color::YELLOW;
        _current_fcol = wcw::color::BLACK;
    }

    void update() override
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        auto time = std::put_time(&tm,"%d-%m-%Y %H:%M:%S");
        std::stringstream sstr;
        sstr << time;
        write_at(sstr.str(), 0, 0);
    }
};

int main()
{
    wcw::console con;
    con.initialize(wcw::rect(0, 0, 40, 20));
    wcw::rect bounds(1, 1, 16, 1);
    container_widget cont(&con, wcw::rect(0, 0, 0, 0));
    cont.add_child(std::make_unique<time_widget>(&con, bounds));
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