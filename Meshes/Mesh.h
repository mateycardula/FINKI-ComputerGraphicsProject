#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <vector>
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "../Shaders/Shader.h"
struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};
class Mesh {
public:
    Mesh();
    virtual ~Mesh();

    virtual void Create() = 0;
    virtual void Render(Shader& shader) = 0;
    virtual void ApplyTransformation(const glm::vec3& scale);

    void setColor(const glm::vec3& color);
    glm::vec3 getColor() const;

    void setPosition(const glm::vec3& newPosition);
    glm::vec3 getPosition() const;

    virtual void setBoundingBox(const std::vector<glm::vec3>& vertices);
    virtual AABB getBoundingBox() const;

    void setRotation(const glm::vec3& newRotation);  // Rotation setter
    glm::vec3 getRotation() const;

protected:
    std::vector<glm::vec3> vertices;
    GLuint VAO, VBO;
    void setupMesh();
    struct Vertex {
        glm::vec3 Position;
        glm::vec2 TexCoords;
    };

    glm::vec3 color;
    glm::vec3 position;
    glm::vec3 rotation;
    AABB boundingBox;
};

#endif // MESH_H
