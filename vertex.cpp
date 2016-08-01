#include "vertex.h"

Vertex Vertex::moveTo(Point p) const
{
    Vertex v(*this);
    v.pos+=p;
    return v;
}

void Vertex::writeToBuffer(std::vector<GLfloat> *vec) const
{
    assert(vec!=nullptr);
    // pre alloc
    vec->reserve(vec->size()+6);
    vec->push_back(pos.x);
    vec->push_back(pos.y);
    vec->push_back(pos.z);

    vec->push_back(color.r);
    vec->push_back(color.g);
    vec->push_back(color.b);
}
