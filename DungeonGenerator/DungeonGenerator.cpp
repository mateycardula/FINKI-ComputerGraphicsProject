//
// Created by mateycardula on 1/26/2024.
//

#include <ctime>
#include <iostream>
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
    this->maxTiles = maxTiles;
    this->gridWidth = gridWidth;
    this->gridDepth = gridDepth;
}

std::vector<DungeonGenerator::Tile> DungeonGenerator::createFloorLayout(std::vector<Mesh *> &sceneMeshes) {
    int i = 0;
    std::vector<Tile> tiles;
    srand(time(nullptr));

    // Start with a seed tile at the center
    Tile seed = {gridWidth / 2, gridDepth / 2};
    tiles.push_back(seed);

    sceneMeshes.push_back(MeshProducer()
                                  .withColor(glm::vec3(0.9f, 0.3f, 0.9f))
                                  .atPosition(glm::vec3(seed.x * 3.0f - (gridWidth/2)*3 , -2.0f, seed.y * 3.0f - (gridDepth/2)*3))
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
                                          .withColor(glm::vec3(0.9f, 0.3f, 0.9f))
                                          .atPosition(glm::vec3(newTile.x * 3.0f - (gridWidth/2)*3 , -2.0f, newTile.y * 3.0f - (gridDepth/2)*3))
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
        glm::vec3 wallColor = glm::vec3(0.6f, 0.3f, 0.3f);
        glm::vec3 wallPosition;
        glm::vec3 wallRotation;

        if (!hasLeftNeighbor) {
            wallPosition = glm::vec3((actualX - 1.5f), -0.5f, actualZ);
            wallRotation = glm::vec3(0.0f, 90.0f, 0.0f); // Rotate 90 degrees around Y-axis
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .CreateWall());
        }
        if (!hasRightNeighbor) {
            wallPosition = glm::vec3(actualX + 1.5f, -0.5f, actualZ);
            wallRotation = glm::vec3(0.0f, 90.0f, 0.0f); // Rotate 90 degrees around Y-axis
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .CreateWall());
        }
        if (!hasTopNeighbor) {
            wallPosition = glm::vec3(actualX, -0.5f, actualZ - 1.5f);
            wallRotation = glm::vec3(0.0f, 0.0f, 0.0f); // No rotation
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
                                          .CreateWall());
        }
        if (!hasBottomNeighbor) {
            wallPosition = glm::vec3(actualX, -0.5f, actualZ + 1.5f);
            wallRotation = glm::vec3(0.0f, 0.0f, 0.0f); // No rotation
            sceneMeshes.push_back(MeshProducer().withColor(wallColor)
                                          .atPosition(wallPosition)
                                          .withRotation(wallRotation)
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
