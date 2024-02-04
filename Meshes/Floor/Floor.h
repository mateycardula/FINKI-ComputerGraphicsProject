//
// Created by mateycardula on 1/26/2024.
//

#ifndef OPENGL_FLOOR_H
#define OPENGL_FLOOR_H
#define GLM_ENABLE_EXPERIMENTAL

#include "../Mesh.h"
#include <glm.hpp>
#include "gtx/string_cast.hpp"

class Floor : public Mesh {
public:
    void Create() override;
    void Create(float gridSize);
private:

};

#endif

//OPENGL_FLOOR_H
