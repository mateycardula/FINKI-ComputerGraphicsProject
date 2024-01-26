//
// Created by mateycardula on 1/26/2024.
//

#ifndef OPENGL_UI_H
#define OPENGL_UI_H


#pragma once
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"

class UI {
public:
    UI(int width, int height);
    void render();
    void startDraw();
    void endDraw();

private:
    int width;
    int height;
    void drawCrosshair();
};


#endif //OPENGL_UI_H
