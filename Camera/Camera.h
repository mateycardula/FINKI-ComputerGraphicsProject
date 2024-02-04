#ifndef CAMERA_H
#define CAMERA_H

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch, float aspect_ratio);
    Camera();
    glm::mat4 GetViewMatrix() const;
    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset);

    glm::vec3 getPosition() const;
    glm::mat4 getProjectionMatrix() const;

    void setAspectRatio(float aspectRatio);

private:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;

    float Fov;
    float AspectRatio;
    float NearPlane;
    float FarPlane;

    void updateCameraVectors();
};

#endif // CAMERA_H
