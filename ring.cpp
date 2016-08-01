#include "ring.h"

Ring::Ring(int planr, MagicCube *m)
    :inner_circle(planr, step_inner, m)
    ,outer_circle(planr, step_outer, m)
{

}

void Ring::rotate(Rotate d)
{
    inner_circle.rotate(d);
    outer_circle.rotate(d);
}
