#ifndef CAMERA_H
#define CAMERA_H
#include <GL/gl.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class Camera_Movement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const GLfloat YAW        = 270.0f;
const GLfloat PITCH      =  0.0f;
const GLfloat ZOOM       =  45.0f;

class Camera
{
public:
    // Constructor with vectors
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
           glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
           GLfloat yaw = YAW, GLfloat pitch = PITCH);

    glm::mat4 GetViewMatrix();

    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();

    void rotate(GLfloat v, GLfloat h);
    void move(Camera_Movement direction, GLfloat s);
    void zoom(GLfloat yoffset);
    GLfloat getZoom() const {return glm::radians(Zoom);}
private:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
public:
    GLfloat Horizontal;
    GLfloat Vertical;
private:
    GLfloat Zoom;
};

#endif // CAMERA_H
