#include <winconw/console_char.hpp>

namespace wcw
{
    std::vector<console_char> console_char::text2vec(
        const std::string& text,
        color fcol,
        color bcol)
    {
        std::vector<console_char> result;
        result.reserve(text.size());
        for(char ch : text)
        {
            result.push_back(console_char(ch, fcol, bcol));
        }
        return result;
    }
}