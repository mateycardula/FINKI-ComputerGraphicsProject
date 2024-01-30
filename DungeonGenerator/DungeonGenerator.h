//
// Created by mateycardula on 1/26/2024.
//

#ifndef OPENGL_DUNGEONGENERATOR_H
#define OPENGL_DUNGEONGENERATOR_H


#include <vector>
#include "../Meshes/Mesh.h"
#include "algorithm"

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



    DungeonGenerator(int maxTiles, int gridWidth, int gridDepth);
    std::vector<Tile> createFloorLayout();
    void placeWalls();
    void generateRooms(std::vector<Mesh *> &sceneMeshes);
    void expandRoom(Room& room, std::vector<Mesh *> &sceneMeshes);


    void setMaxTiles(int maxTiles);
    void setGridWidth(int gridWidth);
    void setGridDepth(int gridDepth);
    void setFloorLayout(std::vector<Tile> &floorLayout);
    bool isRoomTIle(Tile tile);
    Wall* findWall(glm::vec2 position);
    Tile* getFreeNeighbor(Tile& tile);

    void fetchFloorMeshes(std::vector<Mesh*>& sceneMeshes);
    void fetchOuterWallMeshes(std::vector<Mesh*>& sceneMeshes);


private:

    bool tileExists(const std::vector<Tile>& tiles, int x, int y);

    Texture wallTexture;
    Texture floorTexture;
    int maxTiles;
    int gridWidth;
    int gridDepth;

    std::vector<Tile> floorLayout;
    std::vector<Room> rooms;
    std::vector<Wall> walls;

    bool isInBounds(int x, int y);

};


#endif //OPENGL_DUNGEONGENERATOR_H
