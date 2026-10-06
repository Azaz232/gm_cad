#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera(float startDistance)
{
    target = glm::vec3(0.0f, 0.0f, 0.0f); 
    up = glm::vec3(0.0f, 1.0f, 0.0f); 

    distance = startDistance;
    yaw = -90.0f;
    position = glm::vec3(0.0f, 2.0f, distance);

    UpdateCameraPosition();
}

void Camera::UpdateCameraPosition()
{
    float radians = glm::radians(yaw);

    position.x = distance * std::cos(radians);
    position.z = distance * std::sin(radians);
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, target, up);
}

void Camera::ProcessKeyboard(int direction, float deltaTime)
{
    float rotateSpeed = 60.0f * deltaTime; 
    float heightSpeed = 10.0f * deltaTime; 

    if (direction == 1) // W 
    {
        position.y += heightSpeed;
        if (position.y > 20.0f) position.y = 20.0f;
    }
    if (direction == 2) //S
    {
        position.y -= heightSpeed;
        if (position.y < -20.0f) position.y = -20.0f;
    }

    if (direction == 3) //A
    {
        yaw -= rotateSpeed;
    }
    if (direction == 4) //D
    {
        yaw += rotateSpeed;
    }

    UpdateCameraPosition();
}

void Camera::ProcessMouse(float yOffset)
{
    float sensitivity = 0.1f;
    distance -= yOffset * sensitivity;

    if (distance < 3.0f)  distance = 3.0f;
    if (distance > 60.0f) distance = 60.0f;

    UpdateCameraPosition();
}