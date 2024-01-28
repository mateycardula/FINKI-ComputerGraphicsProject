#include <ctime>
#include <iostream>
#include <random>
#include "DungeonGenerator.h"
#include "../Meshes/Factory/Produce/MeshProducer.h"

bool DungeonGenerator::Tile::operator==(const DungeonGenerator::Tile &other) const {
    return x == other.x && y == other.y;
}

void DungeonGenerator::setMaxTiles(int maxTiles) {
    DungeonGenerator::maxTiles = maxTiles;
}

void DungeonGenerator::setGridWidth(int gridWidth) {
    DungeonGenerator::gridWidth = gridWidth;
}

void DungeonGenerator::setGridDepth(int gridDepth) {
    DungeonGenerator::gridDepth = gridDepth;
}

void DungeonGenerator::setFloorLayout(std::vector<Tile> &floorLayout) {
    DungeonGenerator::floorLayout = floorLayout;
}

DungeonGenerator::DungeonGenerator(int maxTiles, int gridWidth, int gridDepth) {
    std::cout<<"Tuka";
    this->maxTiles = maxTiles;
    this->gridWidth = gridWidth;
    this->gridDepth = gridDepth;
    this->floorTexture = Texture("../tex.jpg");
    this->wallTexture = Texture("../t.png");


}

std::vector<DungeonGenerator::Tile> DungeonGenerator::createFloorLayout(std::vector<Mesh *> &sceneMeshes) {
    std::cout<<"TUka";
    int i = 0;
    std::vector<Tile> tiles;
    srand(time(nullptr));

    // Start with a seed tile at the center
    Tile seed = {gridWidth / 2, gridDepth / 2};
    tiles.push_back(seed);

    sceneMeshes.push_back(MeshProducer()
                                  .withColor(glm::vec3(1.0f, 1.0f, 1.0f))
                                  .atPosition(glm::vec3(seed.x * 3.0f - (gridWidth/2)*3 , -2.0f, seed.y * 3.0f - (gridDepth/2)*3))
                                  .withTexture(floorTexture)
                                  .CreateFloor());



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

        if (newTile.x >= 0 && newTile.x < gridWidth && newTile.y >= 0 && newTile.y < gridDepth &&
            !tileExists(tiles, newTile.x, newTile.y)) {
            tiles.push_back(newTile);
            sceneMeshes.push_back(MeshProducer()
                                          .withColor(glm::vec3(1.0f, 1.0f, 1.0f))
                                          .atPosition(glm::vec3(newTile.x * 3.0f - (gridWidth/2)*3 , -2.0f, newTile.y * 3.0f - (gridDepth/2)*3))
                                          .withTexture(floorTexture)
                                          .CreateFloor());

            std::cout<<sceneMeshes.size()<<std::endl;
        }
    }

    setFloorLayout(tiles);
    return tiles;
}

void DungeonGenerator::placeWalls(std::vector<Mesh *> &sceneMeshes) {
    for (const auto& tile : floorLayout) {
        bool hasLeftNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x - 1, tile.y}) != floorLayout.end();
        bool hasRightNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x + 1, tile.y}) != floorLayout.end();
        bool hasTopNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x, tile.y - 1}) != floorLayout.end();
        bool hasBottomNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x, tile.y + 1}) != floorLayout.end();

        float actualX = tile.x * 3.0f - (gridWidth/2)*3;
        float actualZ = tile.y * 3.0f - (gridDepth/2)*3;
        glm::vec3 wallColor = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 wallPosition;
        glm::vec3 wallRotation;

        if (!hasLeftNeighbor) {
            wallPosition = glm::vec3((actualX - 1.5f), -0.5f, actualZ);
            wallRotation = glm::vec3(0.0f, 90.0f, 0.0f); // Rotate 90 degrees around Y-axis
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .withTexture(wallTexture)
                                          .CreateWall());
        }
        if (!hasRightNeighbor) {
            wallPosition = glm::vec3(actualX + 1.5f, -0.5f, actualZ);
            wallRotation = glm::vec3(0.0f, 90.0f, 0.0f); // Rotate 90 degrees around Y-axis
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .withTexture(wallTexture)
                                          .CreateWall());
        }
        if (!hasTopNeighbor) {
            wallPosition = glm::vec3(actualX, -0.5f, actualZ - 1.5f);
            wallRotation = glm::vec3(0.0f, 0.0f, 0.0f); // No rotation
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .withTexture(wallTexture)
                                          .CreateWall());
        }
        if (!hasBottomNeighbor) {
            wallPosition = glm::vec3(actualX, -0.5f, actualZ + 1.5f);
            wallRotation = glm::vec3(0.0f, 0.0f, 0.0f); // No rotation
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .withTexture(wallTexture)
                                          .CreateWall());
        }
    }

}

bool DungeonGenerator::tileExists(const std::vector<Tile> &tiles, int x, int y) {
    for (const auto& tile : tiles) {
        if (tile.x == x && tile.y == y) {
            return true;
        }
    }
    return false;
}

void DungeonGenerator::generateRooms(std::vector<Mesh *> &sceneMeshes) {

    std::random_device rd;
    std::mt19937 gen(rd());

    // Create distribution
    std::uniform_real_distribution<> dis(0.0, 1.0);

    // Generate and output a random number
    double randomValue = dis(gen);
    Room room = *new Room;
    bool currentRoom = true;
    for(Tile floorTile : floorLayout){
        if(!isRoomTIle(floorTile)){
            if(rand() % 100 < 20){
                    room = *new Room;
                    room.color = glm::vec3(dis(gen), dis(gen), dis(gen));
                    rooms.push_back(room);
                    room.tiles.push_back(floorTile);
                    expandRoom(room, sceneMeshes);
            }
        }
    }
}


bool DungeonGenerator::isRoomTIle(DungeonGenerator::Tile tile) {
    for(Room room : rooms){
        for(Tile roomTile : room.tiles){
            if(tile == roomTile) return true;
        }
    }
    return false;
}

void DungeonGenerator::expandRoom(Room& room, std::vector<Mesh *> &sceneMeshes) {
    Tile inspectingTile = room.tiles.at(0);
    bool loop = true;
    while(loop){
        sceneMeshes.push_back(MeshProducer()
                                      .withColor(room.color)
                                      .atPosition(glm::vec3(inspectingTile.x * 3.0f - (gridWidth/2)*3 , -1.0f, inspectingTile.y * 3.0f - (gridDepth/2)*3))
                                      .withTexture(floorTexture)
                                      .CreateFloor());
        if(rand() % 100 < 90){
            std::unique_ptr<Tile> newTile(getFreeNeighbor(inspectingTile));
            if(newTile != nullptr){
                room.tiles.push_back(*newTile);
                inspectingTile = *newTile;
            }
            else{
                loop = false;
            }
        }
        else{
            loop = false;
        }
    }
}

bool DungeonGenerator::isInBounds(int x, int y) {
    Tile inspectingTile = Tile{x, y};
    for(Tile floor: floorLayout){
        if(inspectingTile == floor) return true;
    }
    return false;
}

DungeonGenerator::Tile *DungeonGenerator::getFreeNeighbor(DungeonGenerator::Tile &tile) {
    static const int dx[4] = {0, 1, 0, -1};
    static const int dy[4] = {-1, 0, 1, 0};
    std::vector<Tile> tiles;
    for (int i = 0; i < 4; ++i) {
        int neighborX = tile.x + dx[i];
        int neighborY = tile.y + dy[i];


        if (isInBounds(neighborX, neighborY) && !isRoomTIle(Tile{neighborX, neighborY})) {
            tiles.push_back(Tile{neighborX, neighborY});
        }
    }
    if(tiles.empty())
    return nullptr;
    size_t index = static_cast<size_t>(rand()) % tiles.size();
    return new Tile(tiles.at(index));
}


bool DungeonGenerator::Wall::operator==(const DungeonGenerator::Wall &other) const {
    return false;
}
