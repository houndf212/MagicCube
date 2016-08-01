#include "cube.h"

Cube::Cube(GLfloat x, GLfloat y, GLfloat z)
{
    copyvertex(vertices, Point(x, y, z));
    for (int i=0; i<cube_planr_size; ++i)
    {
        colored_planr[i]=false;
        color[i] = -1;
    }
}

void Cube::initColor(int p)
{
    assert(0<=p && p<cube_planr_size);
    setColor(p, p);
}

void Cube::setColor(int p, int c)
{
    assert(0<=p && p<cube_planr_size);
    assert(0<=c && c<cube_planr_size);

    for (int j=0; j<planr_vertex_size; ++j)
    {
        this->vertices[p][j].color = planr_colors[c];
    }
    colored_planr[p] = true;
    color[p] = c;
}

int Cube::getColor(int p) const
{
    assert(0<=p && p<cube_planr_size);
    assert(colored_planr[p]==true);
    return color[p];
}

void Cube::writeToBuffer(std::vector<GLfloat> *vec) const
{
    for(int i=0; i<cube_planr_size; ++i)
    {
        if (colored_planr[i]==true)
        {
            for (int j=0; j<planr_vertex_size; ++j)
            {
                vertices[i][j].writeToBuffer(vec);
            }
        }
    }
}

void Cube::copyvertex(Vertex to[cube_planr_size][planr_vertex_size], Point center)
{
    for (int i=0; i<cube_planr_size; ++i)
    {
        for (int j=0; j<planr_vertex_size; ++j)
            to[i][j] = cube_vertices[i][j].moveTo(center);
    }
}
