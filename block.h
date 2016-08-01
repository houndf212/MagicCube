#ifndef BLOCK_H
#define BLOCK_H

#include "define.h"

class Block
{
public:
    constexpr Block(int c, int p)
        :cube(c), planr(p)
    {}

    int cube;
    int planr;
};

#endif // BLOCK_H
