#include "circle.h"
#include <algorithm>
#include "magiccube.h"

Circle::Circle(int p, int s, MagicCube *m)
    :planr(p)
    ,step(s)
    ,magic(m)
{
    assert(s==step_inner || s==step_outer);
}

void Circle::rotate(Rotate d)
{
    std::vector<Block> lst;
    switch (step)
    {
    case step_inner:
        lst = {circle_inner[planr], circle_inner[planr]+circle_inner_size};
        break;
    case step_outer:
        lst = {circle_outer[planr], circle_outer[planr]+circle_outer_size};
        break;
    default:
        assert(false);
        break;
    }

    // choose wiche enum to reverse
    if (d == Rotate::Anti_Clock)
        circle_reverse(&lst);

    std::vector<int> last_color;
    last_color.reserve(step);

    { // save step color
        auto begin = lst.cend();
        std::advance(begin, -step);
        for(; begin!=lst.cend(); ++begin)
        {
            last_color.push_back(magic->getColor(*begin));
        }
    }

    { // shift color
        auto from = lst.crbegin();
        std::advance(from, step);
        auto to = lst.crbegin();
        for (; from!=lst.crend(); ++from, ++to)
        {
            magic->setColor(*to, magic->getColor(*from));
        }
    }

    { // set saved color
        auto begl = lst.cbegin();
        auto begv=last_color.cbegin();
        for (; begv!=last_color.cend(); ++begv, ++begl)
        {
            magic->setColor(*begl, *begv);
        }
    }
}

void Circle::circle_reverse(std::vector<Block> *vec)
{
    switch(step)
    {
    case step_outer:
        std::reverse(vec->begin(), vec->end());
        break;
    case step_inner:
    {
        auto iter= vec->begin();
        ++iter;
        std::reverse(iter, vec->end());
    }
        break;
    default:
        assert(false);
    }
}
