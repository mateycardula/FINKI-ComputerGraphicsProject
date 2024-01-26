//
// Created by mateycardula on 1/26/2024.
//

#ifndef OPENGL_FLOOR_H
#define OPENGL_FLOOR_H


#include "../Cube/Cube.h"
#include <glm.hpp>

class Floor : public Cube {
public:
    Floor();
    void Create() override;
private:

};

#endif

//OPENGL_FLOOR_H
