#include <winconw/color.hpp>

WORD wcw::get_char_info_attr(color fcol, color bcol)
{
    WORD attr = 0x0000;

    auto fill_red = [&attr](color col, bool foreground)
    {    
        switch(col)
        {
            case color::WHITE:
            case color::DARK_GRAY:
            case color::RED:
            case color::DARK_RED:
            case color::MAGENTA:
            case color::DARK_MAGENTA:
            case color::YELLOW:
            case color::DARK_YELLOW:

            attr |= foreground ? FOREGROUND_RED : BACKGROUND_RED;
            break;
        }
    };        
    
    auto fill_green = [&attr](color col, bool foreground)
    {
        switch(col)
        {
            case color::WHITE:
            case color::DARK_GRAY:
            case color::GREEN:
            case color::DARK_GREEN:
            case color::YELLOW:
            case color::DARK_YELLOW:
            case color::CYAN:
            case color::DARK_CYAN:

            attr |= foreground ? FOREGROUND_GREEN : BACKGROUND_GREEN;
            break;
        }      
    };

    auto fill_blue = [&attr](color col, bool foreground)
    {
        switch(col)
        {
            case color::WHITE:
            case color::DARK_GRAY:
            case color::BLUE:
            case color::DARK_BLUE:
            case color::CYAN:
            case color::DARK_CYAN:
            case color::MAGENTA:
            case color::DARK_MAGENTA:

            attr |= foreground ? FOREGROUND_BLUE : BACKGROUND_BLUE;
        }
    };

    auto fill_intensity = [&attr](color col, bool foreground)
    {
        switch(col)
        {
            case color::WHITE:
            case color::RED:
            case color::GREEN:
            case color::BLUE:
            case color::MAGENTA:
            case color::YELLOW:
            case color::CYAN:
            case color::GRAY:

            attr |= foreground ? FOREGROUND_INTENSITY : BACKGROUND_INTENSITY;
        }
    };

    fill_red(fcol, true);
    fill_red(bcol, false);
    fill_green(fcol, true);
    fill_green(bcol, false);
    fill_blue(fcol, true);
    fill_blue(bcol, false);
    fill_intensity(fcol, true);
    fill_intensity(bcol, false);

    return attr;
}