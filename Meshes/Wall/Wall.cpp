#include "Wall.h"
#include <gtc/matrix_transform.hpp>

Wall::Wall() : Cube() {
    // Initialization specific to Wall, if any
}

void Wall::Create() {
    Cube::Create();
    glm::vec3 scale = glm::vec3(3.0f, 3.0f, 0.5f);

    for (glm::vec3& vertex : vertices) { // Assuming 'vertices' is accessible from Cube
        vertex = glm::vec3(glm::scale(glm::mat4(1.0f), scale) * glm::vec4(vertex, 1.0f));
    }
    this->setBoundingBox(vertices);
    setupMesh();
}

void Wall::ApplyTransformation(const glm::vec3& scale) {
    // Similar implementation as in the Wall constructor
    // Transform the cube into a wall based on the scale
}