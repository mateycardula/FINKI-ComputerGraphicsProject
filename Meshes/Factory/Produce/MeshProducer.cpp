#include "MeshProducer.h"

Mesh* MeshProducer::CreateWall(float gridSize) {
    Wall* wall = new Wall();
    wall->Create(gridSize);
    attributeAssign(wall);
    return wall;
}

Mesh* MeshProducer::CreateCube() {
    //Cube* cube = new Cube();
    Mesh* cube = new Cube();
    attributeAssign(cube);
    cube->Create();
    return cube;
}

MeshProducer& MeshProducer::withColor(const glm::vec3& color) {
    this->color = color;
    return *this;
}

MeshProducer& MeshProducer::atPosition(const glm::vec3& position) {
    this->position = position;
    return *this;
}

void MeshProducer::attributeAssign(Mesh *mesh) {
    mesh->setColor(color);
    mesh->setPosition(position);
    mesh->setRotation(rotation);
    mesh->setTexture(texture);
}

Mesh *MeshProducer::CreateFloor(float gridSize) {
    Floor* floor = new Floor();
    floor->Create(gridSize);
    attributeAssign(floor);
    return floor;
}

MeshProducer &MeshProducer::withRotation(const glm::vec3 &rotation) {
    this->rotation = rotation;
    return *this;
}

MeshProducer &MeshProducer::withTexture(Texture texture) {
    this->texture = texture;
    return *this;
}