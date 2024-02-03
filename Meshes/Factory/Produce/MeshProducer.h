#ifndef MESHPRODUCER_H
#define MESHPRODUCER_H

#include "../../Wall/Wall.h"
#include "../../Floor/Floor.h"
#include "../../Cube/Cube.h"
#include "../../Mesh.h"
#include "../../Texture.h"
#include <glm.hpp>
#include <memory>


class MeshProducer {
public:
    Mesh* CreateWall(float gridSize);
    Mesh* CreateCube();
    Mesh* CreateFloor(float gridSize);
    static Mesh* CreateTriangle();

    MeshProducer& withColor(const glm::vec3& color);
    MeshProducer& withRotation(const glm::vec3& rotation);
    MeshProducer& atPosition(const glm::vec3& position);
    MeshProducer& withTexture(Texture texture);
    // Add more methods for other mesh types
private:
    glm::vec3 color = glm::vec3(1.0f); // default white
    glm::vec3 position = glm::vec3(0.0f);
    glm::vec3 rotation = glm::vec3 (0.0f);
    Texture texture;
    void attributeAssign(Mesh *mesh);

};
#endif //OPENGL_MESHPRODUCER_H