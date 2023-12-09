#pragma once
#include "grid.h"
#include "position.h"
class MinesweeperGrid : public Grid
{
private:
protected:
    void randomlyPlaceMines();

public:
    MinesweeperGrid(int rows, int cols);
    void reset(int rows, int cols);

    std::vector<Position> mineLocations = {};
};