#include "magiccube.h"
#include "surface.h"

const Cube c_cube[magic_cube_size] =
{
    // first layer
    {-cube_len, cube_len, cube_len}, {0, cube_len, cube_len}, {cube_len, cube_len, cube_len}, //012
    {-cube_len, 0, cube_len}, {0, 0, cube_len}, {cube_len, 0, cube_len}, //345
    {-cube_len, -cube_len, cube_len}, {0, -cube_len, cube_len}, {cube_len, -cube_len, cube_len}, //678
    // second layer
    {-cube_len, cube_len, 0}, {0, cube_len, 0}, {cube_len, cube_len, 0},
    {-cube_len, 0, 0}, {0, 0, 0}, {cube_len, 0, 0},
    {-cube_len, -cube_len, 0}, {0, -cube_len, 0}, {cube_len, -cube_len, 0},
    // third layer
    {-cube_len, cube_len, -cube_len}, {0, cube_len, -cube_len}, {cube_len, cube_len, -cube_len}, //012
    {-cube_len, 0, -cube_len}, {0, 0, -cube_len}, {cube_len, 0, -cube_len}, //345
    {-cube_len, -cube_len, -cube_len}, {0, -cube_len, -cube_len}, {cube_len, -cube_len, -cube_len} //678
};

MagicCube::MagicCube()
    :firstPlanr(0)
{
    initCube();
    initColor();
}

void MagicCube::setFirstPaintPlanr(int p)
{
    assert(0<=p && p<cube_planr_size);
    firstPlanr = p;
}

void MagicCube::writeToBuffer(std::vector<GLfloat> *vec) const
{
    for (int i=0; i<magic_cube_size; ++i)
    {
        cubes[planr_cube_order[firstPlanr][i]].writeToBuffer(vec);
    }
}

void MagicCube::rotate(int planr, Rotate d)
{
    Ring r(planr, this);
    r.rotate(d);
}

void MagicCube::initColor()
{
    for (int i=0; i<surface_cube_size; ++i)
    {
        setColor(Block(surfaces[p_front][i],p_front), p_front);
        setColor(Block(surfaces[p_back][i],p_back), p_back);
        setColor(Block(surfaces[p_up][i],p_up), p_up);
        setColor(Block(surfaces[p_down][i],p_down), p_down);
        setColor(Block(surfaces[p_left][i],p_left), p_left);
        setColor(Block(surfaces[p_right][i],p_right), p_right);
    }
}

void MagicCube::initCube()
{
    for (int i=0; i<magic_cube_size; ++i)
    {
        cubes[i]=c_cube[i];
    }
}

int MagicCube::getColor(Block b) const
{
    return cubes[b.cube].getColor(b.planr);
}

void MagicCube::setColor(Block b, int c)
{
    cubes[b.cube].setColor(b.planr, c);
}
