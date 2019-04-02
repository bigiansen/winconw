#include <winconw/con_char.hpp>

namespace wcw
{
    std::vector<con_char> con_char::text2vec(
        const std::string& text,
        color fcol,
        color bcol)
    {
        std::vector<con_char> result;
        result.reserve(text.size());
        for(char ch : text)
        {
            result.push_back(con_char(ch, fcol, bcol));
        }
        return result;
    }
}