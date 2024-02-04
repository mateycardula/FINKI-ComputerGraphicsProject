#ifndef MESH_H
#define MESH_H
#define GLM_ENABLE_EXPERIMENTAL
#include <vector>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../Shaders/Shader.h"
#include "Texture.h"

struct Vertex {
    glm::vec3 Position;
    glm::vec2 TexCoords;
};

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

class Mesh {
public:
    Mesh();

    virtual void Create() = 0;
    virtual void Render(Shader& shader) = 0;
    virtual void ApplyTransformation(const glm::vec3& scale);

    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const;

    void setPosition(const glm::vec3& newPosition);
    glm::vec3 getPosition() const;

   // virtual void setBoundingBox();
    //virtual AABB getBoundingBox() const;

    void setRotation(const float newRotation);
    float getRotation() const;

    void setTexture(const Texture &texture);

    const Texture &getTexture() const;

    glm::mat4 modelMatrix;

protected:
    std::vector<Vertex> vertices;
    glm::vec3 color;
    glm::vec3 position;
    float rotation;

    Texture texture;
    AABB boundingBox;
};

#endif
