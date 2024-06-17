#pragma once
#include <iostream>

class ArrayUtils
{
public:
    template <typename T>
    static auto PrintArray(const char* name, T* arr, unsigned int size) -> void;

    template <typename T>
    static auto PrintMatrix(const char* name, T** arr, unsigned int rows, unsigned cols) -> void;
};

