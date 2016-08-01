#ifndef RING_H
#define RING_H

#include "circle.h"

class Ring
{
public:
    Ring(int planr, MagicCube* m);
    void rotate(Rotate d);
private:
    Circle inner_circle, outer_circle;
};

#endif // RING_H
