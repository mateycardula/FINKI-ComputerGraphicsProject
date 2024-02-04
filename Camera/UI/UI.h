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
    static void render();
    static void startDraw();
    static void endDraw();
    static bool debugMode;
    static bool renderWalls;
    static bool regenerate;
    static bool generatingWalls;

    static int MAX_TILES;
    static int MAX_WIDTH;
    static int MAX_DEPTH;

    static int numWalls;
    static int numFloors;
    static int FPS;

    static int width;
    static int height;


private:
    static void drawDebugCheckbox();
    static void drawRenderWallsCheckbox();
    static void drawGenerationSettings();
    static void writeText();
    static void drawMeshesCount();
};


#endif //OPENGL_UI_H
