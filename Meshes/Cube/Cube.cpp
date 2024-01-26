#include "Cube.h"

void Cube::Create() {
    vertices = {
            // Positions
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f,  0.5f, -0.5f),
            glm::vec3(0.5f,  0.5f, -0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),

            // Front face
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3(0.5f, -0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f, -0.5f,  0.5f),

            // Left face
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),

            // Right face
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),

            // Bottom face
            glm::vec3(-0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f, -0.5f),
            glm::vec3(0.5f, -0.5f,  0.5f),
            glm::vec3(0.5f, -0.5f,  0.5f),
            glm::vec3(-0.5f, -0.5f,  0.5f),
            glm::vec3(-0.5f, -0.5f, -0.5f),

            // Top face
            glm::vec3(-0.5f,  0.5f, -0.5f),
            glm::vec3(0.5f,  0.5f, -0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f,  0.5f),
            glm::vec3(-0.5f,  0.5f, -0.5f)
    };

    this->setBoundingBox(vertices);
    setupMesh();
}

void Cube::Render(Shader& shader) {
    shader.Use();
    //shader.setVec3("meshColor", getColor());

    //glm::mat4 model = glm::translate(glm::mat4(1.0f), position);
    //shader.setMat4("model", model);

    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // 6 faces * 2 triangles * 3 vertices
    glBindVertexArray(0);
}
