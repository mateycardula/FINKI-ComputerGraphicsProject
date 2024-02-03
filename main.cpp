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

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

std::vector<Mesh*> sceneMeshes;


int main(){

    GLFWwindow* mainWindow = nullptr;

    Init app(WIDTH, HEIGHT, "211029");

    if (!app.initializeApplication(&mainWindow)) {
        if (mainWindow) glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return -1;
    }

    Shader myShader("../Shaders/vShader.txt", "../Shaders/fShader.txt");
    MeshProducer meshProducer;
    ImGuiManager imguiManager(mainWindow);  // Initialize ImGui
    UI ui(WIDTH, HEIGHT);
    Raycaster raycaster(app);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_DEPTH_TEST);

    int maxTiles = 1600;
    int gridWidth = 500;
    int gridDepth = 100;

    DungeonGenerator generator = *new DungeonGenerator(maxTiles, gridWidth, gridDepth);
    generator.createFloorLayout();
    generator.generateRooms(sceneMeshes);
    generator.fetchFloorMeshes(sceneMeshes);
    generator.placeWalls();
    generator.fetchOuterWallMeshes(sceneMeshes);



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



        for (Mesh* mesh : sceneMeshes) {
            AABB box = mesh->getBoundingBox();
//            if (raycaster.intersectsWithAABB(box)) {
//                myShader.setVec3("meshColor", glm::vec3(0.2f, 0.5f, 0.2f));
//            } else {
//                myShader.setVec3("meshColor", mesh->getColor());
//            }

            glm::vec3 rotation = mesh->getRotation();

            glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

            glm::mat4 rotationMatrix = rotZ * rotY * rotX;
            glm::mat4 model = glm::translate(glm::mat4(1.0f), mesh->getPosition()) * rotationMatrix;
            myShader.setMat4("model", model);
            mesh->Render(myShader);
        }

        ui.render();

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwDestroyWindow(mainWindow);
    glfwTerminate();
    return 0;
}
