#include <ctime>
#include <iostream>
#include <random>
#include "DungeonGenerator.h"
#include "../Meshes/Factory/Produce/MeshBuilder.h"
#include "../Camera/UI/UI.h"
#include <chrono>
#include <iomanip>

float DungeonGenerator::gridSize;
int roomID = -1;

void DungeonGenerator::setMaxTiles(int maxTiles) {
    DungeonGenerator::maxTiles = maxTiles;

}

void DungeonGenerator::setGridWidth(int gridWidth) {
    DungeonGenerator::gridWidth = gridWidth;
}

void DungeonGenerator::setGridDepth(int gridDepth) {
    DungeonGenerator::gridDepth = gridDepth;
}

DungeonGenerator::DungeonGenerator(int maxTiles, int gridWidth, int gridDepth, float gridSize) {
    this->gridSize = gridSize;
    UI::MAX_WIDTH = gridWidth;
    UI::MAX_DEPTH = gridDepth;
    UI::MAX_TILES = maxTiles;
    regenerate(maxTiles, gridWidth, gridDepth);

}

void DungeonGenerator::createFloorLayout() {
    srand(time(nullptr));

    int tileLimit = gridWidth * gridDepth;
    Tile seed = {gridWidth / 2, gridDepth / 2};
    addTile(seed.x, seed.y, seed);
    while (tilesMap.size() < maxTiles && tilesMap.size() < tileLimit) {
        int expandIndex = rand() % tilesMap.size();
        auto it = std::begin(tilesMap);
        std::advance(it, expandIndex);
        Tile base = it->second;

        int direction = rand() % 4;
        Tile newTile = base;
        switch (direction) {
            case 0: newTile.y -= 1; break; // Up
            case 1: newTile.y += 1; break; // Down
            case 2: newTile.x -= 1; break; // Left
            case 3: newTile.x += 1; break; // Right
        }

        if (newTile.x >= 0 && newTile.x < gridWidth && newTile.y >= 0 && newTile.y < gridDepth &&
            !findTile(newTile.x, newTile.y)) {
            addTile(newTile.x, newTile.y, newTile);
        }
    }
}

void DungeonGenerator::placeWalls() {
    static const float dx[4] = {0, 0.5f, 0, -0.5f};
    static const float dy[4] = {-0.5f, 0, 0.5f, 0};

    static const int dxt[4] = {0, 1, 0, -1};
    static const int dyt[4] = {-1, 0, 1, 0};

    for (const auto& pair : tilesMap){
        Tile tile = pair.second;
        int x = pair.first.first;
        int y = pair.first.second;
        for(int i = 0; i < 4; i++){
            Tile* neighbor = findTile(x + dxt[i], y + dyt[i]);
            if (!neighbor) {
                Wall wall;
                wall.rotation = 90.0f * i;
                addWall((float)x + dx[i], y + dy[i], wall);
            }
        }
    }

    for(const auto& room : rooms){

        std::vector<Wall> myWalls;
        std::vector<Wall *> neigbouringWalls;

        bool placedDoor = false;
        bool foundDoor = false;

        for(auto& tile : room.tiles){
            int x = tile.x;
            int y = tile.y;
            for(int i = 0; i < 4; i++){
                Tile* neighbor = findTile(x + dxt[i], y + dyt[i]);
                if(neighbor){
                    if(neighbor->roomID == tile.roomID) continue;

                    Wall* foundWall = findWall(x + dx[i], y + dy[i]);
                    if(foundWall) {
                        if(foundWall->isDoorWay) foundDoor = true;
                        neigbouringWalls.push_back(foundWall);
                    }
                    else{
                        Wall newWall;
                        newWall.rotation =  90.0f * i;
                        newWall.position = {x + dx[i], y + dy[i]};
                        if(rand()%100 < 10){
                            newWall.isDoorWay = true;
                            placedDoor = true;
                        }
                        myWalls.push_back(newWall);
                        addWall(x + dx[i], y + dy[i], newWall);
                    }
                }
            }
        }

        if(!placedDoor && !myWalls.empty()){
            size_t index = static_cast<size_t>(rand()) % myWalls.size();
            Wall wall = myWalls.at(index);
            findWall(wall.position.x, wall.position.y)->isDoorWay = true;
        }

        if(!foundDoor && !neigbouringWalls.empty()){
            size_t index = static_cast<size_t>(rand()) % neigbouringWalls.size();
            neigbouringWalls.at(index)->isDoorWay = true;
        }
    }
}

void DungeonGenerator::generateRooms() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 1.0);

    for (const auto& pair : tilesMap){
        Tile* floorTile = findTile(pair.first.first, pair.first.second);
        if(floorTile->roomID==-1){
            roomID++;
            floorTile->roomID = roomID;
            glm::vec3 roomColor = {dis(gen), dis(gen), dis(gen)};

            expandRoom(floorTile, roomColor);
        }
    }
}

void DungeonGenerator::expandRoom(Tile* root, glm::vec3 roomColor){
    Room room;
    room.tiles.push_back(*root);

    int i = 0;
    root->color = roomColor;

    Tile inspectingTile = *root;
    while(true){
        if(rand() % 100 < 100 - i){
            Tile* newTile(getFreeNeighbor(inspectingTile.x, inspectingTile.y));
            if(newTile != nullptr){
                newTile->roomID = roomID;
                newTile->color = roomColor;
                room.tiles.push_back(*newTile);
                inspectingTile = *newTile;
                i++;
            }
            else{
                rooms.push_back(room);
                return;
            }

        }
        else {
            rooms.push_back(room);
            return;
        }
    }
}

DungeonGenerator::Tile *DungeonGenerator::getFreeNeighbor(int x, int y) {
    static const int dx[4] = {0, 1, 0, -1};
    static const int dy[4] = {-1, 0, 1, 0};
    std::vector<Tile*> tiles;
    for (int i = 0; i < 4; ++i) {
        int neighborX = x + dx[i];
        int neighborY = y + dy[i];

        Tile *neigbourTile = findTile(neighborX, neighborY);
        if(!neigbourTile) continue;

        if(neigbourTile->roomID == -1){
            tiles.push_back(neigbourTile);
        }
    }
    if(tiles.empty())
        return nullptr;
    size_t index = static_cast<size_t>(rand()) % tiles.size();
    return tiles.at(index);
}


void DungeonGenerator::fetchFloorMeshes(std::vector<glm::mat4> &modelMatrices, std::vector<glm::vec3> &colors) {

    modelMatrices.clear();
    colors.clear();
    for (const auto& pair : tilesMap){
        int x = pair.first.first;
        int z = pair.first.second;
        Tile tile = pair.second;

        Mesh * floor = MeshBuilder()
                .withColor(tile.color)
                .atPosition(glm::vec3(x * 3.0f - (gridWidth/2)*3 , -2.0f, z * 3.0f - (gridDepth/2)*3))
                .CreateFloor(gridSize);

        modelMatrices.push_back(floor->modelMatrix);
        colors.push_back(floor->getColor());
    }
}

void DungeonGenerator::fetchWallMeshes(std::vector<glm::mat4> &modelMatrices, std::vector<glm::vec3> &colors) {
    glm::vec3 wallRotation;

    modelMatrices.clear();
    colors.clear();
    for(const auto& pair : wallsMap){
        float x = pair.first.first;
        float z = pair.first.second;
        Wall wall = pair.second;

        float actualX = x * 3.0f - (gridWidth/2)*3;
        float actualZ = z * 3.0f - (gridDepth/2)*3;
        Mesh* newWall;
        if(wall.isDoorWay) {
            wall.color = {0.5f, 1.0f, 0.2f};
            newWall = MeshBuilder()
                    .withColor(wall.color)
                    .withRotation(wall.rotation)
                    .atPosition(glm::vec3(actualX , -0.5f, actualZ))
                    .CreateDoor(gridSize);

        }
        else {
            newWall = MeshBuilder()
                    .withColor(wall.color)
                    .withRotation(wall.rotation)
                    .atPosition(glm::vec3(actualX, -0.5f, actualZ))
                    .CreateWall(gridSize);
        }

        modelMatrices.push_back(newWall->modelMatrix);
        colors.push_back(newWall->getColor());
    }
}

void DungeonGenerator::regenerate(int maxTiles, int gridWidth, int gridDepth) {
    roomID = -1;
    UI::generatingWalls = true;
    UI::render();
    tilesMap.clear();
    wallsMap.clear();
    rooms.clear();

    setMaxTiles(maxTiles);
    setGridWidth(gridWidth);
    setGridDepth(gridDepth);
    createFloorLayout();
    generateRooms();
    placeWalls();
}
