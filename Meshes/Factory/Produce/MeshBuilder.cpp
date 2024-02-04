#include "MeshBuilder.h"

Mesh* MeshBuilder::CreateWall(float gridSize) {
    Wall* wall = new Wall();
    attributeAssign(wall);
    wall->Create(gridSize);
    return wall;
}

Mesh* MeshBuilder::CreateDoor(float gridSize) {
    Doorway* door = new Doorway();
    attributeAssign(door);
    door->Create(gridSize);
    return door;
}

MeshBuilder& MeshBuilder::withColor(const glm::vec3& color) {
    this->color = color;
    return *this;
}

MeshBuilder& MeshBuilder::atPosition(const glm::vec3& position) {
    this->position = position;
    return *this;
}

void MeshBuilder::attributeAssign(Mesh *mesh) {
    mesh->setColor(color);
    mesh->setPosition(position);
    mesh->setRotation(rotation);
}

Mesh *MeshBuilder::CreateFloor(float gridSize) {
    Floor* floor = new Floor();
    attributeAssign(floor);
    floor->Create(gridSize);
    return floor;
}

MeshBuilder &MeshBuilder::withRotation(const float rotation) {
    this->rotation = rotation;
    return *this;
}

