#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include "../Camera/Camera.h"

class InputManager {
public:
    static void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

private:
    static float lastX;
    static float lastY;
    static bool firstMouse;
    static bool cursorLocked;

};

#endif // INPUTMANAGER_H
