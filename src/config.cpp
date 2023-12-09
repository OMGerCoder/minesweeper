#include "config.h"
#include "grid.h"
#include <raylib.h>
Config::Config() : cellSize(30), cellSpacing(5), mineCount(10), rows(20), cols(20), garbage(59305)
{

    cellColors.insert(std::make_pair(NIL, RAYWHITE));
    cellColors.insert(std::make_pair(MINE, RED));
    cellColors.insert(std::make_pair(ZERO, RAYWHITE));
    cellColors.insert(std::make_pair(ONE, Color{0, 0, 255, 255}));
    cellColors.insert(std::make_pair(TWO, Color{0, 130, 0, 255}));
    cellColors.insert(std::make_pair(THREE, Color{255, 0, 0, 255}));
    cellColors.insert(std::make_pair(FOUR, Color{0, 0, 132, 255}));
    cellColors.insert(std::make_pair(FIVE, Color{0, 0, 132, 255}));
    cellColors.insert(std::make_pair(SIX, Color{0, 130, 132, 255}));
    cellColors.insert(std::make_pair(SEVEN, Color{132, 0, 132, 255}));
    cellColors.insert(std::make_pair(EIGHT, Color{117, 117, 117, 255}));
}
struct Config config;