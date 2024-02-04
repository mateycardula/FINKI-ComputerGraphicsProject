

#include <iostream>


#include "Mesh.h"
#include "gtx/string_cast.hpp"

Mesh::Mesh() {
}


void Mesh::ApplyTransformation(const glm::vec3& scale) {
    // Implement transformation logic if necessary
}

void Mesh::setColor(const glm::vec3& newColor) {
    color = newColor;
}

glm::vec3 Mesh::getColor() const {
    return color;
}

void Mesh::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
}

glm::vec3 Mesh::getPosition() const {
    return position;
}

void Mesh::setRotation(const float newRotation) {
    rotation = newRotation;
}

float Mesh::getRotation() const {
    return rotation;
}

void Mesh::setTexture(const Texture &texture) {
    Mesh::texture = texture;
}

const Texture &Mesh::getTexture() const {
    return texture;
}

