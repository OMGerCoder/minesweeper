#pragma once
#include <vector>

namespace utility
{
    template <typename T>
    int indexOf(std::vector<T> vector, T element)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            if (element == vector[i])
            {
                return i;
            }
        }
        return -1;
    }
    bool isValidCell(int x, int y, int cols, int rows);
    bool isInBetween(int input, int lowerBound, int upperBound);
}