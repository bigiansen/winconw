#include <winconw/widget.hpp>
#include <winconw/console.hpp>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <chrono>

class time_widget : public wcw::widget
{
public:
    time_widget(wcw::console* con_ptr, wcw::rect bounds_rect)
        : widget(con_ptr, bounds_rect)
    { }

    void update() override
    {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        auto time = std::put_time(&tm,"%d-%m-%Y %H:%M:%S");
        std::stringstream sstr;
        sstr << time;
        std::vector<wcw::con_char> row = 
            wcw::con_char::text2vec(sstr.str(), wcw::color::BLACK, wcw::color::YELLOW);
        _char_rows.clear();
        _char_rows.push_back(row);
    }
};

int main()
{
    wcw::console con;
    con.initialize(wcw::rect(0, 0, 40, 20));
    wcw::rect bounds(1, 1, 16, 1);
    time_widget wdg(&con, bounds);
    while(true)
    {
        using namespace std::chrono_literals;
        std::this_thread::sleep_for(100ms);
        wdg.update();
        wdg.draw();
    }
    int i = 0;
    std::cin >> i;
    return 0;
}