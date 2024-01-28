//
// Created by mateycardula on 1/25/2024.
//

#ifndef OPENGL_WALL_H
#define OPENGL_WALL_H


#include "../Cube/Cube.h"
#include <glm.hpp>

class Wall : public Cube {
public:
    Wall();
    void Create() override;
    void ApplyTransformation(const glm::vec3& scale) override;
private:

};

#endif