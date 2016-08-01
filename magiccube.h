#ifndef MAGICCUBE_H
#define MAGICCUBE_H

#include "cube.h"
#include "ring.h"
#include "surface.h"

constexpr int magic_cube_size = 3*9;

constexpr Point planr_normal_vec[cube_planr_size] =
{
    {0, 0, 1},
    {0, 0,-1},
    {0, 1, 0},
    {0, 1, 0}, //planr down is reverse
   {-1, 0, 0},
    {1, 0, 0}
};

constexpr int planr_cube_order[cube_planr_size][magic_cube_size] =
{
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26},
    {18,19,20,21,22,23,24,25,26, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,16,17},
    {18,19,20, 9,10,11, 0, 1, 2, 3, 4, 5, 6, 7, 8,12,13,14,15,16,17,21,22,23,24,25,26},
    {24,25,26,15,16,17, 6, 7, 8, 0, 1, 2, 3, 4, 5, 9,10,11,12,13,14,18,19,20,21,22,23},
    {18, 9, 0,21,12, 3,24,15, 6, 1, 2, 4, 5, 7, 8,10,11,13,14,16,17,19,20,22,23,25,26},
    { 2,11,20, 5,14,23, 8,17,26, 0, 1, 3, 4, 6, 7, 9,10,12,13,15,16,18,19,21,22,24,25}
};

class MagicCube
{
    friend class Circle;
public:
    MagicCube();
    void setFirstPaintPlanr(int p);
    void writeToBuffer(std::vector<GLfloat>* vec) const;
    void rotate(int planr, Rotate d);
private:
    void initColor();
    void initCube();

    int getColor(Block b) const;
    void setColor(Block b, int c);
private:
    Cube cubes[magic_cube_size];
    int firstPlanr;
};

#endif // MAGICCUBE_H
