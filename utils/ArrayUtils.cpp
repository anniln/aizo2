#include "ArrayUtils.h"

template <typename T>
void ArrayUtils::PrintArray(const char* name, T* arr, unsigned size)
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
void ArrayUtils::PrintMatrix(const char* name, T** arr, unsigned rows, unsigned cols)
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
