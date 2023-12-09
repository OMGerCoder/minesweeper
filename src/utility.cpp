#include "utility.h"
bool utility::isValidCell(int x, int y, int cols, int rows)
{
    return y >= 0 && y < rows && x >= 0 && x < cols;
}
bool utility::isInBetween(int input, int lowerBound, int upperBound)
{
    return input > lowerBound && input < upperBound;
}