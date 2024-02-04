#ifndef MESHPRODUCER_H
#define MESHPRODUCER_H

#include "../../Wall/Wall.h"
#include "../../Doorway/Doorway.h"
#include "../../Floor/Floor.h"
#include "../../Mesh.h"
#include "../../Texture.h"
#include <glm.hpp>
#include <memory>


class MeshBuilder {
public:
    Mesh* CreateWall(float gridSize);
    Mesh* CreateFloor(float gridSize);
    Mesh* CreateDoor(float gridSize);

    MeshBuilder& withColor(const glm::vec3& color);
    MeshBuilder& withRotation(const float rotation);
    MeshBuilder& atPosition(const glm::vec3& position);

private:
    glm::vec3 color = glm::vec3(1.0f); // default white
    glm::vec3 position = glm::vec3(0.0f);
    float rotation = 0.0f;
    void attributeAssign(Mesh *mesh);

};
#endif //OPENGL_MESHPRODUCER_H