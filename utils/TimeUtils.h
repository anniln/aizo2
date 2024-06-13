#pragma once
#include <string>
#include <ctime>
#include <iomanip>

#include "NumberUtils.h"

using namespace std;

class TimeUtils
{
public:
    static std::string CurrentTimeAsString()
    {
        std::time_t currentTime = std::time(nullptr);
        std::tm localTime;
        localtime_s(&localTime, &currentTime);

        std::stringstream ss;
        ss << put_time(&localTime, "%Y%m%d_%H%M%S");
        return ss.str();
    }

    static std::string FormatMicrosecondToMilliseconds(long microsec)
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(3) << microsec / 1000.0;
        return NumberUtils::ReplaceDotWithSemicolon(ss.str());
    }
};
