//
// Created by mateycardula on 1/25/2024.
//

#ifndef OPENGL_WALL_H
#define OPENGL_WALL_H
#define GLM_ENABLE_EXPERIMENTAL


#include "../Cube/Cube.h"
#include <glm.hpp>

class Wall : public Cube {
public:
    Wall();
    void Create(float gridSize);
private:

};

#endif