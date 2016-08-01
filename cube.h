#ifndef CUBE_H
#define CUBE_H

#include "define.h"
#include <vector>

class Cube
{
public:
    Cube(GLfloat x=0, GLfloat y=0, GLfloat z=0);
    void initColor(int p);

    void setColor(int p, int c);
    int getColor(int p) const;

    void writeToBuffer(std::vector<GLfloat> *vec) const;
private:
    Vertex vertices[cube_planr_size][planr_vertex_size];
    bool colored_planr[cube_planr_size];
    int color[cube_planr_size];
private:
    static void copyvertex(Vertex to[cube_planr_size][planr_vertex_size], Point center);
};

#endif // CUBE_H
