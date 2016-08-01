#include "camera.h"

#include <QtCore>

Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch)
    : Front(glm::vec3(0.0f, 0.0f, -1.0f)),
      Zoom(ZOOM)
{
    this->Position = position;
    this->WorldUp = up;
    this->Horizontal = yaw;
    this->Vertical = pitch;
    this->updateCameraVectors();
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(this->Position, this->Position + this->Front, this->Up);
}

void Camera::updateCameraVectors()
{
    // Calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(this->Horizontal)) * cos(glm::radians(this->Vertical));
    front.y = sin(glm::radians(this->Vertical));
    front.z = sin(glm::radians(this->Horizontal)) * cos(glm::radians(this->Vertical));
    this->Front = glm::normalize(front);
    // Also re-calculate the Right and Up vector
    this->Right = glm::normalize(glm::cross(this->Front, this->WorldUp));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    this->Up    = glm::normalize(glm::cross(this->Right, this->Front));
    this->Position = -3.0f*Front;
//    qDebug() << "front:" <<Position.x<<","<<Position.y<<","<<Position.z;
//    qDebug() << Horizontal;
//    qDebug() << Vertical;
}

void Camera::rotate(GLfloat v, GLfloat h)
{
    Horizontal += h;
    Vertical   += v;

    if (Horizontal > 360.0f)
        Horizontal-=360.0f;
    else if (Horizontal<-0.0f)
        Horizontal+=360.0f;

    const GLfloat an = 30.0f;
    Vertical = qBound(-an, Vertical, an);


    // Update Front, Right and Up Vectors using the updated Eular angles
    this->updateCameraVectors();
}

void Camera::move(Camera_Movement direction, GLfloat s)
{
    if (direction == Camera_Movement::FORWARD)
        this->Position += this->Front * s;
    if (direction == Camera_Movement::BACKWARD)
        this->Position -= this->Front * s;
    if (direction == Camera_Movement::LEFT)
        this->Position -= this->Right * s;
    if (direction == Camera_Movement::RIGHT)
        this->Position += this->Right * s;
}

void Camera::zoom(GLfloat yoffset)
{
    if (this->Zoom >= 1.0f && this->Zoom <= 100.0f)
        this->Zoom -= yoffset;
    if (this->Zoom <= 1.0f)
        this->Zoom = 1.0f;
    if (this->Zoom >= 100.0f)
        this->Zoom = 100.0f;

//    qDebug() << Zoom;
}
