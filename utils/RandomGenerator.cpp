﻿#include "RandomGenerator.h"

#include <random>

int RandomGenerator::random(int min, int max)
{
    static std::random_device rd; 
    static std::mt19937 gen(rd()); 
    std::uniform_int_distribution<> distr(min, max);
    return distr(gen);
}

