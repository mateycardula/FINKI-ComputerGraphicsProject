#include "Wall.h"
#include "gtx/string_cast.hpp"
#include <gtc/matrix_transform.hpp>
#include <iostream>

void Wall::Create(float gridSize) {
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, position);
    model = glm::rotate(model, glm::radians(rotation), {0.0f, 1.0f, 0.0f});
    model = glm::scale(model, glm::vec3(gridSize, gridSize, 0.2f));
    this->modelMatrix = model;
}

void Wall::Create() {

}




