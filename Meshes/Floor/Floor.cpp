//
// Created by mateycardula on 1/26/2024.
//

#include "Floor.h"

Floor::Floor() {

}

void Floor::Create() {
    Cube::Create();
    glm::vec3 scale = glm::vec3(3.0f, 0.2f, 3.0f);

    for (glm::vec3& vertex : vertices) { // Assuming 'vertices' is accessible from Cube
        vertex = glm::vec3(glm::scale(glm::mat4(1.0f), scale) * glm::vec4(vertex, 1.0f));
    }
    this->setBoundingBox(vertices);
    setupMesh();
}
