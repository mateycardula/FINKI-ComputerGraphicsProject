#include "Camera.h"
#include <gtc/matrix_transform.hpp>
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float aspect_ratio)
        : Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(2.5f), MouseSensitivity(0.1f),
          Position(position), WorldUp(up), Yaw(yaw), Pitch(pitch),
          Fov(45.0f), AspectRatio(aspect_ratio), NearPlane(0.1f), FarPlane(1000.0f) {
    updateCameraVectors();
}

Camera::Camera() {}

glm::mat4 Camera::GetViewMatrix() const{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime) {
    float velocity = MovementSpeed * deltaTime;
    if (direction == FORWARD)
        Position += Front * velocity;
    if (direction == BACKWARD)
        Position -= Front * velocity;
    if (direction == LEFT)
        Position -= Right * velocity;
    if (direction == RIGHT)
        Position += Right * velocity;
}

void Camera::ProcessMouseMovement(float xoffset, float yoffset) {
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    if (Pitch > 89.0f)
        Pitch = 89.0f;
    if (Pitch < -89.0f)
        Pitch = -89.0f;

    updateCameraVectors();
}

void Camera::updateCameraVectors() {
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    Right = glm::normalize(glm::cross(Front, WorldUp));
    Up = glm::normalize(glm::cross(Right, Front));
}

glm::vec3 Camera::getPosition() const {
    return Position;
}

glm::mat4 Camera::getProjectionMatrix() const {
    return glm::perspective(glm::radians(Fov), AspectRatio, NearPlane, FarPlane);
}

void Camera::setAspectRatio(float aspectRatio) {
    std::cout<<"ASPECT ";
    AspectRatio = aspectRatio;
}
