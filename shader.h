#ifndef SHADER_H
#define SHADER_H

#include <GL/gl.h>
#include <GLES3/gl3.h>

class Shader
{
public:
    Shader() : Program(0) {}
    bool compile(const GLchar *vertexPath, const GLchar* fragmentPath);
    void Use() { glUseProgram(Program); }
    GLuint Program;
};

#endif // SHADER_H
