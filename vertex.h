#ifndef VERTEX_H
#define VERTEX_H

#include <GL/gl.h>
#include <glm/vec3.hpp>
#include <vector>

typedef glm::vec3 Point;
typedef glm::vec3 Color;

class Vertex
{
public:
    constexpr Vertex(GLfloat x=0, GLfloat y=0, GLfloat z=0)
        :pos(Point(x, y, z))
//          ,color(Color(0, 0, 0))
    {}

    Vertex moveTo(Point p) const;

    void writeToBuffer(std::vector<GLfloat> *vec) const;

    Point pos;
    Color color;

    static constexpr int Buffer_Size = 6;
};

#endif // VERTEX_H
