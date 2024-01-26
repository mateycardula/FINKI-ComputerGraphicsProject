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

using namespace std;

const GLint WIDTH = 800, HEIGHT = 600;

std::vector<Mesh*> sceneMeshes;

struct Tile {
    int x, y;

    bool operator==(const Tile& other) const {
        return x == other.x && y == other.y;
    }
};

bool tileExists(const std::vector<Tile>& tiles, int x, int y) {
    for (const auto& tile : tiles) {
        if (tile.x == x && tile.y == y) {
            return true;
        }
    }
    return false;
}

std::vector<Tile> createFloorLayout(int maxTiles, int gridWidth, int gridHeight) {
    std::vector<Tile> tiles;
    srand(time(nullptr)); // Seed random number generator

    // Start with a seed tile at the center
    Tile seed = {gridWidth / 2, gridHeight / 2};
    tiles.push_back(seed);

    while (tiles.size() < maxTiles) {
        // Randomly select an existing tile to expand from
        int expandIndex = rand() % tiles.size();
        Tile base = tiles[expandIndex];

        // Randomly determine direction to expand (up, down, left, right)
        int direction = rand() % 4;
        Tile newTile = base;
        switch (direction) {
            case 0: newTile.y -= 1; break; // Up
            case 1: newTile.y += 1; break; // Down
            case 2: newTile.x -= 1; break; // Left
            case 3: newTile.x += 1; break; // Right
        }

        // Check if the new tile is within the grid and doesn't already exist
        if (newTile.x >= 0 && newTile.x < gridWidth && newTile.y >= 0 && newTile.y < gridHeight &&
            !tileExists(tiles, newTile.x, newTile.y)) {
            tiles.push_back(newTile);
        }
    }

    return tiles;
}

void placeWalls(std::vector<Mesh*>& sceneMeshes, const std::vector<Tile>& floorLayout, int gridWidth, int gridDepth) {
    for (const auto& tile : floorLayout) {
        bool hasLeftNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x - 1, tile.y}) != floorLayout.end();
        bool hasRightNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x + 1, tile.y}) != floorLayout.end();
        bool hasTopNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x, tile.y - 1}) != floorLayout.end();
        bool hasBottomNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x, tile.y + 1}) != floorLayout.end();

        float actualX = tile.x * 3.0f; // Assuming each tile is 3x3 units
        float actualZ = tile.y * 3.0f;
        glm::vec3 wallColor = glm::vec3(0.6f, 0.3f, 0.3f);
        glm::vec3 wallPosition;
        glm::vec3 wallRotation;

        // Add walls based on missing neighbors
        if (!hasLeftNeighbor) {
            wallPosition = glm::vec3(actualX - 1.5f, 1.5f, actualZ);
            wallRotation = glm::vec3(0.0f, 90.0f, 0.0f); // Rotate 90 degrees around Y-axis
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .CreateWall());
        }
        if (!hasRightNeighbor) {
            wallPosition = glm::vec3(actualX + 1.5f, 1.5f, actualZ);
            wallRotation = glm::vec3(0.0f, 90.0f, 0.0f); // Rotate 90 degrees around Y-axis
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .CreateWall());
        }
        if (!hasTopNeighbor) {
            wallPosition = glm::vec3(actualX, 1.5f, actualZ - 1.5f);
            wallRotation = glm::vec3(0.0f, 0.0f, 0.0f); // No rotation
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .CreateWall());
        }
        if (!hasBottomNeighbor) {
            wallPosition = glm::vec3(actualX, 1.5f, actualZ + 1.5f);
            wallRotation = glm::vec3(0.0f, 0.0f, 0.0f); // No rotation
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .CreateWall());
        }
    }
}


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

    glEnable(GL_DEPTH_TEST);

    int maxTiles = 200; // Maximum number of floor tiles
    int gridWidth = 25; // Width of the grid
    int gridHeight = 40;


    std::vector<Tile> floorLayout = createFloorLayout(maxTiles, gridWidth, gridHeight);

    for (const auto& tile : floorLayout) {
        sceneMeshes.push_back(MeshProducer()
                                      .withColor(glm::vec3(0.9f, 0.3f, 0.9f))
                                      .atPosition(glm::vec3(tile.x * 3.0f, 0.0f, tile.y * 3.0f))
                                      .CreateFloor());
        cout<<"Floor placed "<<endl;
    }

    placeWalls(sceneMeshes,floorLayout, gridWidth, gridHeight);

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
            if (raycaster.intersectsWithAABB(box)) {
                myShader.setVec3("meshColor", glm::vec3(0.2f, 0.5f, 0.2f));
            } else {
                myShader.setVec3("meshColor", mesh->getColor());
            }

            glm::vec3 rotation = mesh->getRotation();

// Create a rotation matrix for each axis
            glm::mat4 rotX = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            glm::mat4 rotY = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            glm::mat4 rotZ = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));

// Combine the rotation matrices
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
