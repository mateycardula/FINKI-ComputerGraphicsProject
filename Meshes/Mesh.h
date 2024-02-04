#ifndef MESH_H
#define MESH_H
#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../Shaders/Shader.h"
#include "Texture.h"

class Mesh {
public:
    Mesh();

    virtual void Create() = 0;

    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const;

    void setPosition(const glm::vec3& newPosition);
    glm::vec3 getPosition() const;

    void setRotation(const float newRotation);
    float getRotation() const;


    glm::mat4 modelMatrix;
protected:
    glm::vec3 color;
    glm::vec3 position;
    float rotation;

    Texture texture;
};

#endif
