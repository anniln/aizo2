#pragma once
#include <string>
#include <ctime>
#include <iomanip>

using namespace std;

class NumberUtils
{
public:
    static std::string ReplaceDotWithSemicolon(const std::string& numberIn);
};

inline std::string NumberUtils::ReplaceDotWithSemicolon(const std::string& numberIn)
{
    std::string numberOut = numberIn;
    for (char& ch : numberOut)
    {
        if (ch == '.')
        {
            ch = ',';
        }
    }
    return numberOut;
}
