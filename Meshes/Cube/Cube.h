//
// Created by mateycardula on 1/25/2024.
//

#ifndef OPENGL_CUBE_H
#define OPENGL_CUBE_H


#include "../Mesh.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"

class Cube : public Mesh {


public:
    void Create() override;
    void Render(Shader& shader)  override;
};

#endif//OPENGL_CUBE_H
