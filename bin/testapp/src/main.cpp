#include <winconw/console.hpp>
#include <iostream>

int main()
{
    wcw::console con;
    con.initialize(wcw::rect(0, 0, 40, 20));
    int i;
    con.set_text_color(wcw::color::DARK_YELLOW);
    con.write("Hello my friend");
    std::cin >> i;
    return 0;
}