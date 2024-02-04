//
// Created by mateycardula on 1/25/2024.
//

#ifndef OPENGL_WALL_H
#define OPENGL_WALL_H


#include <glm.hpp>
#include "../Mesh.h"

class Wall : public Mesh{
public:
    void Create() override;
    void Create(float gridSize);
private:

};

#endif