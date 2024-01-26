//
// Created by mateycardula on 1/25/2024.
//

#ifndef OPENGL_TRIANGLE_H
#define OPENGL_TRIANGLE_H


#include "../Mesh.h"

class Triangle : public Mesh {
public:
    void Create() override;
    void Render(Shader& shader) override;
};

#endif // TRIANGLE_H
