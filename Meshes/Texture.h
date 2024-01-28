//
// Created by mateycardula on 1/27/2024.
//

#ifndef OPENGL_TEXTURE_H
#define OPENGL_TEXTURE_H


#include "GL/glew.h"

class Texture {
public:
    Texture();
    Texture(const char *path);

    GLuint textureID{};
};


#endif //OPENGL_TEXTURE_H
