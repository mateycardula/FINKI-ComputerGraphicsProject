//
// Created by mateycardula on 1/25/2024.
//

#include "Raycaster.h"

Raycaster::Raycaster(Init& app): app(app){

}

glm::vec3 Raycaster::getRayDirection() {

    double centerX = app.width / 2.0;
    double centerY = app.height / 2.0;

    glm::vec4 rayClip = glm::vec4(
            (2.0 * centerX) / app.width - 1.0,
            1.0 - (2.0 * centerY) / app.height,
            -1.0, 1.0
    );

    glm::vec4 rayEye = glm::inverse(app.camera.getProjectionMatrix()) * rayClip;
    rayEye = glm::vec4(rayEye.x, rayEye.y, -1.0, 0.0);

    glm::vec3 rayWorld = glm::vec3(glm::inverse(app.camera.GetViewMatrix()) * rayEye);
    return glm::normalize(rayWorld);
}

bool Raycaster::intersectsWithAABB(const AABB& box) {
    float tMin = -INFINITY, tMax = INFINITY;

    for (int i = 0; i < 3; ++i) {
        float invD = 1.0f / getRayDirection()[i];
        float t0 = (box.min[i] - app.camera.getPosition()[i]) * invD;
        float t1 = (box.max[i] - app.camera.getPosition()[i]) * invD;
        if (invD < 0.0f) std::swap(t0, t1);
        tMin = std::max(tMin, t0);
        tMax = std::min(tMax, t1);
        if (tMax <= tMin) return false;
    }
    return true;
}

