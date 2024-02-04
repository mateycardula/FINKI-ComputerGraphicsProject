#define GLM_ENABLE_EXPERIMENTAL


#include "refactor.h"
#include "Meshes/Factory/Produce/MeshProducer.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include <gtx/string_cast.hpp>
#include "Camera/Raycaster.h"
#include "Camera/UI/ImGuiManager.h"
#include "Camera/UI/UI.h"
#include "algorithm"
#include "DungeonGenerator/DungeonGenerator.h"
#include "Include/stb_image.h"
#include "Meshes/Texture.h"
#include "Meshes/GeometryManager.h"

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;


std::vector<Mesh*> sceneMeshes;

void render(const std::vector<glm::mat4>& modelMatrices, const std::vector<glm::vec3> &colors) {
    GeometryManager::getInstance()->updateInstanceModelMatrices(modelMatrices);
    GeometryManager::getInstance()->updateColorVector(colors);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, modelMatrices.size()); // 36 vertices for a cube
}


int main(){

    GLFWwindow* mainWindow = nullptr;

    Init app(WIDTH, HEIGHT, "211029");

    if (!app.initializeApplication(&mainWindow)) {
        if (mainWindow) glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }


    glEnable(GL_DEPTH_TEST);

    Shader myShader("../Shaders/vShader.txt", "../Shaders/fShader.txt");
    MeshProducer meshProducer;
    ImGuiManager imguiManager(mainWindow);  // Initialize ImGui
    UI ui(WIDTH, HEIGHT);
    Raycaster raycaster(app);

    Texture floorTexture = Texture("C:\\Users\\mateycardula\\CLionProjects\\OpenGL\\tex.jpg");
    Texture wallTexture = Texture("C:\\Users\\mateycardula\\CLionProjects\\OpenGL\\t.png");

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, floorTexture.textureID);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, wallTexture.textureID);

    int maxTiles = 5000;
    int gridWidth = 500;
    int gridDepth = 100;
    float gridSize = 3;


    std::vector<glm::mat4> floorInstanceMatrices;
    std::vector<glm::vec3> floorInstanceColors;

    std::vector<glm::mat4> wallInstanceMatrices;
    std::vector<glm::vec3> wallInstanceColors;

    DungeonGenerator generator = *new DungeonGenerator(maxTiles, gridWidth, gridDepth, gridSize);
    generator.createFloorLayout();
    generator.generateRooms(sceneMeshes);
    generator.fetchFloorMeshes(floorInstanceMatrices, floorInstanceColors);


    generator.placeWalls();

    generator.fetchOuterWallMeshes(wallInstanceMatrices, wallInstanceColors);

    GLuint cubeVAO = GeometryManager::getInstance()->getCubeVAO();
    glBindVertexArray(cubeVAO);

    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(mainWindow)){
        float currentFrame = glfwGetTime();
        float deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        InputManager::processInput(mainWindow, app.camera, deltaTime);

        glClearColor(0.3f, 0.5f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        myShader.Use();
        glm::mat4 view = app.camera.GetViewMatrix();
        myShader.setMat4("view", view);

        glm::mat4 projection = app.camera.getProjectionMatrix();
        myShader.setMat4("projection", projection);

        myShader.setInt("textureSampler", 0);
        render(floorInstanceMatrices, floorInstanceColors);

        myShader.setInt("textureSampler", 1);
        render(wallInstanceMatrices, wallInstanceColors);
        ui.render();

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();


    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 0;
}
