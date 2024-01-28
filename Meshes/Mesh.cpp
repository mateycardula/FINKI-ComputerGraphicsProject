

#include <iostream>


#include "Mesh.h"

Mesh::Mesh() : VAO(0), VBO(0) {
}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Position));
    glEnableVertexAttribArray(0);

    // Texture coordinates attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
    setBoundingBox();
}

glm::vec3 Mesh::getPosition() const {
    return position;
}

void Mesh::setBoundingBox() {
    if (!vertices.empty()) {
        glm::vec3 min = vertices[0].Position;
        glm::vec3 max = vertices[0].Position;

        glm::mat4 rotMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1, 0, 0));
        rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0));
        rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1));

        for (const auto& vertex : vertices) {
            glm::vec4 rotatedVertex = rotMatrix * glm::vec4(vertex.Position, 1.0f);
            min = glm::min(min, glm::vec3(rotatedVertex));
            max = glm::max(max, glm::vec3(rotatedVertex));
        }

        min += position;
        max += position;

        boundingBox.min = min;
        boundingBox.max = max;
    }
}

AABB Mesh::getBoundingBox() const {
    return boundingBox;
}

void Mesh::setRotation(const glm::vec3& newRotation) {
    rotation = newRotation;
    setBoundingBox();
}

glm::vec3 Mesh::getRotation() const {
    return rotation;
}

void Mesh::setTexture(const Texture &texture) {
    Mesh::texture = texture;
}

