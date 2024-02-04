//
// Created by mateycardula on 2/4/2024.
//

#ifndef OPENGL_DOORWAY_H
#define OPENGL_DOORWAY_H

#include "../Mesh.h"

class Doorway : public  Mesh {
public:
    void Create() override;
    void Create(float gridSize);
};


#endif //OPENGL_DOORWAY_H
