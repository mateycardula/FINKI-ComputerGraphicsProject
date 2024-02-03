//
// Created by mateycardula on 1/26/2024.
//

#ifndef OPENGL_DUNGEONGENERATOR_H
#define OPENGL_DUNGEONGENERATOR_H


#include <vector>
#include "../Meshes/Mesh.h"
#include "algorithm"
#include "../Meshes/Factory/Produce/MeshProducer.h"
#include <optional>
#include <unordered_map>
#include <utility>

namespace std {
    template<> struct hash<pair<int, int>> {
        size_t operator()(const pair<int, int>& p) const {
            auto hash1 = hash<int>{}(p.first);
            auto hash2 = hash<int>{}(p.second);
            return hash1 ^ (hash2 << 1);
        }
    };
}

class DungeonGenerator {
public:
    enum Direction{
        LEFT,
        RIGHT,
        TOP,
        BOTTOM
    };

    struct Tile {
        int x, y;
        glm::vec3 color = {1.0f, 1.0f, 1.0f};
        bool operator==(const Tile& other) const;
        bool operator<(const Tile& other) const {
            return x < other.x || (x == other.x && y < other.y);
        }
        int roomID = -1;
    };

    struct Room{
        std::vector<Tile> tiles;
        glm::vec3 color = {1.0f, 1.0f, 1.0f};
        float y_val;
    };

    struct Wall{
        glm::vec2 position;
        Direction dir;
        bool isDoorWay = false;
        bool isInnerWall = false;

        glm::vec3 leftRotation = {0.0f, 90.0f, 0.0f};
        glm::vec3 rightRotation = {0.0f, 90.0f, 0.0f};
        glm::vec3 topRotation = {0.0f, 0.0f, 0.0f};
        glm::vec3 bottomRotation = {0.0f, 0.0f, 0.0f};

        glm::vec3 color = {1.0f, 1.0f, 1.0f};
        bool operator==(const Wall& other) const;
    };

    struct Blueprints{
        Mesh* notRotatedWall = MeshProducer().withTexture(wallTexture).withRotation({0.0f, 0.0f, 0.0f}).CreateWall(gridSize);
        Mesh* rotatedWall = MeshProducer().withTexture(wallTexture).withRotation({0.0f, 90.0f, 0.0f}).CreateWall(gridSize);
        Mesh* floorInstance = MeshProducer().withTexture(floorTexture).CreateFloor(gridSize);
    };



    DungeonGenerator(int maxTiles, int gridWidth, int gridDepth, float gridSize);
    std::vector<Tile> createFloorLayout();
    void placeWalls();
    void generateRooms(std::vector<Mesh *> &sceneMeshes);
    void expandRoom(Tile* inspectingTile, glm::vec3 roomColor);


    void setMaxTiles(int maxTiles);
    void setGridWidth(int gridWidth);
    void setGridDepth(int gridDepth);

    void setFloorLayout(std::vector<Tile> &floorLayout);
    bool isRoomTIle(Tile tile);
    Wall* findWall(glm::vec2 position);
    Tile* getFreeNeighbor(int x, int y);

    void fetchFloorMeshes(std::vector<Mesh*>& sceneMeshes);
    void fetchOuterWallMeshes(std::vector<Mesh*>& sceneMeshes);


private:
    std::unordered_map<std::pair<int, int>, Tile> tilesMap;

    bool tileExists(const std::vector<Tile>& tiles, int x, int y);
    std::optional<std::reference_wrapper<Tile>> findFloorTile(int x, int y);
    static Texture wallTexture;
    static Texture floorTexture;
    int maxTiles;

    int gridWidth;
    int gridDepth;
    static float gridSize;

    std::vector<Tile> floorLayout;
    std::vector<Room> rooms;
    std::vector<Wall> walls;

    bool isInBounds(int x, int y);

    void addTile(int x, int y, const Tile& tile) {
        tilesMap[{x, y}] = tile;
    }


    Tile* findTile(int x, int y) {
        auto it = tilesMap.find({x, y});
        if (it != tilesMap.end()) {
            return &(it->second);
        }
        return nullptr;
    }

};


#endif //OPENGL_DUNGEONGENERATOR_H
