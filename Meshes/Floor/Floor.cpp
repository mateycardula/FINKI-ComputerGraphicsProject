//
// Created by mateycardula on 1/26/2024.
//

#include "Floor.h"

Floor::Floor() {

}

void Floor::Create(float gridSize) {
    Cube::Create();
    glm::vec3 scale = glm::vec3(gridSize, 0.2f, gridSize);
    for (auto& vertex : vertices) {
        vertex.Position = glm::vec3(glm::scale(glm::mat4(1.0f), scale) * glm::vec4(vertex.Position, 1.0f));
    }
    this->setBoundingBox();
    setupMesh();
}
