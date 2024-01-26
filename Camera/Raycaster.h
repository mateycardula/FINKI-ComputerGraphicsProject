//
// Created by mateycardula on 1/25/2024.
//
//
#ifndef OPENGL_RAYCASTER_H
#define OPENGL_RAYCASTER_H

#include "glm.hpp"
#include "../Meshes/Mesh.h"
#include "GLFW/glfw3.h"
#include "Camera.h"
#include "../init.h"

class Raycaster {
public:
    Raycaster(Init& app);
    bool intersectsWithAABB(const AABB& box);
    glm::vec3 getRayDirection();

private:

    Init& app;

};


#endif //OPENGL_RAYCASTER_H
