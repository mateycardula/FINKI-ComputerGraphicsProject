//
// Created by mateycardula on 1/25/2024.
//

#include <string>
#include "MeshFactory.h"

Mesh* MeshFactory::CreateMesh(ShapeType shapeType) {
    switch (shapeType) {
        case ShapeType::Cube:
            return new Cube();
        case ShapeType::Wall:
            return new Wall();
        default:
            return nullptr;
    }
}

