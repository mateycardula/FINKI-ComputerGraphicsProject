#ifndef OPENGL_MESHFACTORY_H
#define OPENGL_MESHFACTORY_H


#include "../Mesh.h"
#include "../Cube/Cube.h"
#include "../Wall/Wall.h"
#include "MeshParameters.h"
#include "../Types/ShapeType.h"// Include specific shapes here

class MeshFactory {
public:
    static Mesh* CreateMesh(ShapeType shapeType);
};

#endif
