#ifndef OPENGL_IMGUIMANAGER_H
#define OPENGL_IMGUIMANAGER_H


#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <GLFW/glfw3.h>

class ImGuiManager {
public:
    ImGuiManager(GLFWwindow* window);
    ~ImGuiManager();
};


#endif //OPENGL_IMGUIMANAGER_H
