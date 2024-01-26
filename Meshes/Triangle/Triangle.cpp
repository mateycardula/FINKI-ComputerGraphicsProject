#include "Triangle.h"

void Triangle::Create() {
     vertices = {
           glm::vec3( -1.0f, -1.0f, 0.0f),
           glm::vec3(1.0f, -1.0f, 0.0f),
             glm::vec3(0.0f,  1.0f, 0.0f)
    };

    setupMesh();
}

void Triangle::Render(Shader& shader) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}
