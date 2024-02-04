#define GLM_ENABLE_EXPERIMENTAL


#include "refactor.h"
#include "Meshes/Factory/Produce/MeshBuilder.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <gtx/string_cast.hpp>
#include "Camera/UI/ImGuiManager.h"
#include "Camera/UI/UI.h"
#include "algorithm"
#include "DungeonGenerator/DungeonGenerator.h"
#include "Include/stb_image.h"
#include "Meshes/Texture.h"
#include "Meshes/GeometryManager.h"

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

int MAX_TILES = 1000;
int MAX_WIDTH = 5000;
int MAX_DEPTH = 5000;
bool regenerating = false;
float gridSize = 3;


std::vector<glm::mat4> floorInstanceMatrices;
std::vector<glm::vec3> floorInstanceColors;

std::vector<glm::mat4> wallInstanceMatrices;
std::vector<glm::vec3> wallInstanceColors;

std::vector<Mesh*> sceneMeshes;

void render(const std::vector<glm::mat4>& modelMatrices, const std::vector<glm::vec3> &colors) {
    GeometryManager::getInstance()->updateInstanceModelMatrices(modelMatrices);
    GeometryManager::getInstance()->updateColorVector(colors);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, modelMatrices.size()); // 36 vertices for a cube
}

void regenerate(DungeonGenerator& generator){
    MAX_TILES = UI::MAX_TILES;
    MAX_WIDTH = UI::MAX_WIDTH;
    MAX_DEPTH = UI::MAX_DEPTH;

    regenerating = true;
    generator.regenerate(MAX_TILES, MAX_WIDTH, MAX_DEPTH);
    generator.fetchFloorMeshes(floorInstanceMatrices, floorInstanceColors);
    generator.fetchWallMeshes(wallInstanceMatrices, wallInstanceColors);
    regenerating = false;
    UI::regenerate = false;
    UI::numWalls = wallInstanceMatrices.size();
    UI::numFloors = floorInstanceMatrices.size();
}


int main(){
    Init app(WIDTH, HEIGHT, "211029");

    if (!app.initializeApplication()) {
        if (Init::window) glfwDestroyWindow(Init::window);
        glfwTerminate();
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    Shader myShader("../Shaders/vShader.txt", "../Shaders/fShader.txt");
    MeshBuilder meshProducer;
    ImGuiManager imguiManager(Init::window);  // Initialize ImGui
    UI ui(WIDTH, HEIGHT);

    Texture floorTexture = Texture("../floor_texture.jpg");
    Texture wallTexture = Texture("../wall_texture.jpg");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTexture.textureID);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, wallTexture.textureID);


    DungeonGenerator generator(MAX_TILES, MAX_WIDTH, MAX_DEPTH, gridSize);

    regenerate(generator);
    GLuint cubeVAO = GeometryManager::getInstance()->getCubeVAO();
    glBindVertexArray(cubeVAO);

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(Init::window)){
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        UI::FPS = 1/deltaTime;
        lastFrame = currentFrame;

        InputManager::processInput(Init::window, app.camera, deltaTime);


        glClearColor(0.3f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.Use();


        if(UI::regenerate) regenerate(generator);

        if(!regenerating)
        {
            glm::mat4 view = app.camera.GetViewMatrix();
            myShader.setMat4("view", view);

            glm::mat4 projection = app.camera.getProjectionMatrix();
            myShader.setMat4("projection", projection);
            myShader.setBool("useInstanceColor", ui.debugMode);

            myShader.setInt("textureSampler", 0);
            render(floorInstanceMatrices, floorInstanceColors);

            if (UI::renderWalls) {
                myShader.setInt("textureSampler", 1);
                render(wallInstanceMatrices, wallInstanceColors);
            }

            UI::render();
        }


        glfwSwapBuffers(Init::window);
        glfwPollEvents();
    }

    glfwDestroyWindow(Init::window);
    glfwTerminate();
    return 0;
}
