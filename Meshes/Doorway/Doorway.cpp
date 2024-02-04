//
// Created by mateycardula on 2/4/2024.
//

#include "Doorway.h"

void Doorway::Create(float gridSize) {
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::translate(model, {position.x, gridSize/6, position.z});
    model = glm::rotate(model, glm::radians(rotation), {0.0f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(gridSize, gridSize/3, 0.2f));

    this->modelMatrix = model;
}

void Doorway::Create() {

}
