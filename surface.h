#ifndef SURFACE_H
#define SURFACE_H

#include "block.h"

constexpr int surfaces[cube_planr_size][surface_cube_size] =
{
    { 0, 1, 2, 3, 4, 5, 6, 7, 8},
    {18,19,20,21,22,23,24,25,26},
    {18,19,20, 9,10,11, 0, 1, 2},
    {24,25,26,15,16,17, 6, 7, 8},
    {18, 9, 0,21,12, 3,24,15, 6},
    { 2,11,20, 5,14,23, 8,17,26}
};

#endif // SURFACE_H
