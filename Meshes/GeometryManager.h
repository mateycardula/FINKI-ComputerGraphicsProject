#ifndef GEOMETRYMANAGER_H
#define GEOMETRYMANAGER_H

#include <vector>
#include <glm.hpp>
#include "GL/glew.h"
class GeometryManager {
public:
    static GeometryManager* getInstance();
    ~GeometryManager();

    void updateInstanceModelMatrices(const std::vector<glm::mat4>& modelMatrices);
    void updateColorVector(const std::vector<glm::vec3>& colors);
    GLuint getCubeVAO() const;

    GeometryManager(GeometryManager const&) = delete;
    void operator=(GeometryManager const&) = delete;

private:
    static GeometryManager* instance;
    GLuint cubeVAO, cubeVBO, instanceModelMatrixVBO, instanceColorVBO;

    GeometryManager(); // Constructor is private to prevent instantiation
    void setupCubeGeometry();
};

#endif // GEOMETRYMANAGER_H
