﻿#pragma once
#include <string>
#include <ctime>
#include <iomanip>

#include "NumberUtils.h"

using namespace std;

class TimeUtils
{
public:
    static std::string CurrentTimeAsString();

    static std::string FormatMicrosecondToMilliseconds(long long microsec);
};

inline std::string TimeUtils::CurrentTimeAsString()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &currentTime);

    std::stringstream ss;
    ss << put_time(&localTime, "%Y%m%d_%H%M%S");
    return ss.str();
}

inline std::string TimeUtils::FormatMicrosecondToMilliseconds(long long microsec)
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(3) << microsec / 1000.0;
    return NumberUtils::ReplaceDotWithSemicolon(ss.str());
}
