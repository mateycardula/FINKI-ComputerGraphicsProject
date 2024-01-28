#include "Cube.h"

void Cube::Create() {
    vertices = {
            // Back face
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 0.0f}},

            // Front face
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 1.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},

            // Left face
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},

            // Right face
            {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},

            // Bottom face
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f, -0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
            {{0.5f, -0.5f,  0.5f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f,  0.5f}, {0.0f, 0.0f}},
            {{-0.5f, -0.5f, -0.5f}, {0.0f, 1.0f}},

            // Top face
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}},
            {{0.5f,  0.5f, -0.5f}, {1.0f, 1.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
            {{0.5f,  0.5f,  0.5f}, {1.0f, 0.0f}},
            {{-0.5f,  0.5f,  0.5f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f, -0.5f}, {0.0f, 1.0f}}
    };

    this->setBoundingBox();
    setupMesh();
}

void Cube::Render(Shader& shader) {
    shader.Use();
    glBindTexture(GL_TEXTURE_2D, texture.textureID);
    shader.setInt("texture1", 0);
    shader.setVec3("meshColor", color);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 36); // 6 faces * 2 triangles * 3 vertices
    glBindVertexArray(0);
}
