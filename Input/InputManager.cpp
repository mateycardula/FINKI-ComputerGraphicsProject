#include "InputManager.h"
#include "../Camera/UI/UI.h"

float InputManager::lastX = 400;
float InputManager::lastY = 300;
bool InputManager::firstMouse = true;
bool InputManager::cursorLocked = true;

static bool tabKeyWasPressedLastFrame = false;

void InputManager::processInput(GLFWwindow* window, Camera& camera, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);

    bool tabKeyPressed = glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS;
    if (tabKeyPressed && !tabKeyWasPressedLastFrame) {
        cursorLocked = !cursorLocked;
        if (cursorLocked) {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPos(window, 800.0 / 2.0, 600.0 / 2.0); // Adjust as needed
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
    }
    tabKeyWasPressedLastFrame = tabKeyPressed;
}

void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos) {
    if(!cursorLocked) return;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    Camera* camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera)
        camera->ProcessMouseMovement(xoffset, yoffset);
}

void InputManager::framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
    UI::width = width;
    UI::height = height;
    Camera* camera = reinterpret_cast<Camera*>(glfwGetWindowUserPointer(window));
    if(camera) camera->setAspectRatio((float)width/(float)height);
}
