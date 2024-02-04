//
// Created by mateycardula on 12/29/2023.
//

#include "init.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

#include <iostream>

using namespace std;

GLFWwindow* Init::window = nullptr;

Init::Init(int width, int height, const char* title) {
    this->width = width;
    this->height = height;
    this->title=title;
}

Init::Init() {

}

bool Init::initializeGLFW() {
    if (!glfwInit()) {
        cout << "Failed GLFW initialization";
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    return true;
}

GLFWwindow* Init::createWindow(int width, int height, const char* title) {
    GLFWwindow* newWindow = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!newWindow) {
        cout << "Failed to open a window.";
        return nullptr;
    }
    window = newWindow;
    return window;
}

bool Init::initializeGLEW() {
    glfwMakeContextCurrent(window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        cout << "Failed GLEW initialization";
        return false;
    }
    return true;
}

bool Init::initializeApplication() {
    if (!initializeGLFW()) {
        return false;
    }

    window = createWindow(width, height, title);
    if (!(window)) {
        glfwTerminate();
        return false;
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

    if (!initializeGLEW()) {
        glfwDestroyWindow(window);
        glfwTerminate();
        return false;
    }
    glViewport(0, 0, bufferWidth, bufferHeight);

    float camera_ratio = (float)bufferWidth/(float) bufferHeight;
    camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, camera_ratio);
    glfwSetWindowUserPointer(window, &camera);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, InputManager::mouseCallback);
    glfwSetFramebufferSizeCallback(window, InputManager::framebuffer_size_callback);


    return true;
}