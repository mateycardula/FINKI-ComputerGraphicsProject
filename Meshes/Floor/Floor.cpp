#include <iostream>
#include "Floor.h"

Floor::Floor() {

}

void Floor::Create(float gridSize) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::scale(model, glm::vec3(gridSize, 0.2f, gridSize));
    this->modelMatrix = model;
}
