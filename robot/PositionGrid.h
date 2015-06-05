#ifndef PICONTROLLER_POSITIONGRID_H
#define PICONTROLLER_POSITIONGRID_H

class PositionGrid {
    int width;
    int height;
    bool grid[][];
public:
    PositionGrid(int width, int height);
    void fill(int x, int y);
    void open(int x, int y);
    bool isOpen(int x, int y);
};

#endif