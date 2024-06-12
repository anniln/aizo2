#pragma once
#include <iostream>

class ArrayUtils
{
public:
    template <typename T>
    static void PrintArray(const char* name, T* arr, unsigned int size)
    {
        std::cout << "\n" << name << "=";
        for (int i = 0; i < size; i++)
        {
            std::cout << "[" << i << ":" << arr[i] << "] ";
        }
        std::cout << "\n";
        std::cout.flush();
    }
    
    template <typename T>
    static void PrintMatrix(const char* name, T** arr, unsigned int rows, unsigned cols)
    {
        std::cout << "\n" << name << "=";
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; ++j)
            {
                std::cout << "[" << i << "," << j << ":" << arr[i][j] << "] ";
            }
        }
        std::cout << "\n";
        std::cout.flush();
    }
};
