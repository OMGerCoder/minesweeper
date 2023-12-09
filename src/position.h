#pragma once
struct Position
{
    int x;
    int y;
    bool operator<(const Position &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
};