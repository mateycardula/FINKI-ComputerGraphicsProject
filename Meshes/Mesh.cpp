#include "Mesh.h"

Mesh::Mesh() : VAO(0), VBO(0) {

}

Mesh::~Mesh() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


}

void Mesh::ApplyTransformation(const glm::vec3& scale) {

}

void Mesh::setColor(const glm::vec3& newColor) {
    color = newColor;
}

glm::vec3 Mesh::getColor() const {
    return color;
}

void Mesh::setPosition(const glm::vec3& newPosition) {
    position = newPosition;
    setBoundingBox(vertices);
}

glm::vec3 Mesh::getPosition() const {
    return position;
}

void Mesh::setBoundingBox(const std::vector<glm::vec3>& vertices) {
    if (!vertices.empty()) {
        glm::vec3 min = vertices[0];
        glm::vec3 max = vertices[0];

        glm::mat4 rotMatrix(1.0f);
        rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.x), glm::vec3(1, 0, 0)); // X-axis rotation
        rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.y), glm::vec3(0, 1, 0)); // Y-axis rotation
        rotMatrix = glm::rotate(rotMatrix, glm::radians(rotation.z), glm::vec3(0, 0, 1)); // Z-axis rotation

        for (const auto& vertex : vertices) {
            glm::vec4 rotatedVertex = rotMatrix * glm::vec4(vertex, 1.0f);
            min = glm::min(min, glm::vec3(rotatedVertex));
            max = glm::max(max, glm::vec3(rotatedVertex));
        }

        // Apply the object's position
        min = position + min;
        max = position + max;

        boundingBox.min = min;
        boundingBox.max = max;
    }
}


AABB Mesh::getBoundingBox() const {
    return boundingBox;
}

void Mesh::setRotation(const glm::vec3& newRotation) {
    rotation = newRotation;
    setBoundingBox(vertices);
}

glm::vec3 Mesh::getRotation() const {
    return rotation;
}



