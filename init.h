//
// Created by mateycardula on 12/29/2023.
//

#ifndef OPENGL_INIT_H
#define OPENGL_INIT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Input/InputManager.h"


class Init{
public:
    Init(int width, int height, const char* title);
    Init();

    bool initializeApplication();

    bool initializeGLFW();
    GLFWwindow* createWindow(int width, int height, const char* title);
    bool initializeGLEW();
    Camera camera;
    int width;
    int height;
    static GLFWwindow * window;

private:
    const char* title;


};


#endif //OPENGL_INIT_H
