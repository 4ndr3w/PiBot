#include "PositionGrid.h"

PositionGrid::PositionGrid(int width, int height) {
    grid = new bool[width][height];
    this->width = width;
    this->height = height;
}

void PositionGrid::fill(int x, int y) {
    grid[x][y] = true;
}
void PositionGrid::open(int x, int y) {
    grid[x][y] = false;
}
void PositionGrid::isOpen(int x, int y) {
    return grid[x][y];
}