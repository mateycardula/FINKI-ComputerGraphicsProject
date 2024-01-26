#include "MeshProducer.h"

Mesh* MeshProducer::CreateWall() {
    Mesh* wall = new Wall();
    wall->Create();
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
    // Assuming Create() sets default scale
    mesh->setColor(color);
    mesh->setPosition(position);
    mesh->setRotation(rotation);
}

Mesh *MeshProducer::CreateFloor() {
    Mesh* floor = new Floor();
    floor->Create();
    attributeAssign(floor);
    return floor;
}

MeshProducer &MeshProducer::withRotation(const glm::vec3 &rotation) {
    this->rotation = rotation;
    return *this;
}
