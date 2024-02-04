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

    template<> struct hash<pair<float, float>> {
        size_t operator()(const pair<float, float>& p) const {
            auto hash1 = hash<float>{}(p.first);
            auto hash2 = hash<float>{}(p.second);
            return hash1 ^ (hash2 << 1);
        }
    };
}

class DungeonGenerator {
public:

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
    };

    struct Wall{
        glm::vec2 position;
        bool isDoorWay = false;
        bool isInnerWall = false;

        float rotation = 0.0f;
        glm::vec3 color = {1.0f, 1.0f, 1.0f};
        bool operator==(const Wall& other) const;
    };




    DungeonGenerator(int maxTiles, int gridWidth, int gridDepth, float gridSize);
    void createFloorLayout();
    void placeWalls();

    void generateRooms(std::vector<Mesh *> &sceneMeshes);
    void expandRoom(Tile* inspectingTile, glm::vec3 roomColor);


    void setMaxTiles(int maxTiles);
    void setGridWidth(int gridWidth);
    void setGridDepth(int gridDepth);



    Tile* getFreeNeighbor(int x, int y);

    void fetchFloorMeshes(std::vector<glm::mat4> &modelMatrices, std::vector<glm::vec3> &colors);
    void fetchOuterWallMeshes(std::vector<glm::mat4> &modelMatrices, std::vector<glm::vec3> &colors);


private:
    std::unordered_map<std::pair<int, int>, Tile> tilesMap;
    std::unordered_map<std::pair<float, float>, Wall> wallsMap;


    static Texture wallTexture;
    static Texture floorTexture;
    int maxTiles;

    int gridWidth;
    int gridDepth;
    static float gridSize;

    std::vector<Wall> walls;
    std::vector<Room> rooms;

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

    Wall* findWall(float x, float y) {
        auto it = wallsMap.find({x, y});
        if (it != wallsMap.end()) {
            return &(it->second);
        }
        return nullptr;
    }

    void addWall(float x, float y, const Wall& wall){
        wallsMap[{x, y}] = wall;
    }
};


#endif //OPENGL_DUNGEONGENERATOR_H
