#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GLFW/glfw3.h>
#include "../Camera/Camera.h"

class InputManager {
public:
    static void processInput(GLFWwindow* window, Camera& camera, float deltaTime);
    static void mouseCallback(GLFWwindow* window, double xpos, double ypos);

private:
    static float lastX;
    static float lastY;
    static bool firstMouse;

};

#endif // INPUTMANAGER_H
