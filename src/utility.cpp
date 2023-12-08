#include "utility.h"
template <typename T> int indexOf(std::vector<T> vector, T element) {
    for (size_t i = 0; i < vector.size(); i++)
    {
        if (element == vector[i])
        {
            return i;
        }
        
    }
    return -1;
}