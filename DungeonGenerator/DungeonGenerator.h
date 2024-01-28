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
        bool operator==(const Tile& other) const;
    };

    struct Room{
        std::vector<Tile> tiles;
        glm::vec3 color;
    };

    struct Wall{
        Tile tile;
        Direction direction;
        bool operator==(const Wall& other) const;
    };



    DungeonGenerator(int maxTiles, int gridWidth, int gridDepth);
    std::vector<Tile> createFloorLayout(std::vector<Mesh*>& sceneMeshes);
    void placeWalls(std::vector<Mesh*>& sceneMeshes);
    void generateRooms(std::vector<Mesh *> &sceneMeshes);
    void expandRoom(Room& room, std::vector<Mesh *> &sceneMeshes);

    void setMaxTiles(int maxTiles);
    void setGridWidth(int gridWidth);
    void setGridDepth(int gridDepth);
    void setFloorLayout(std::vector<Tile> &floorLayout);
    bool isRoomTIle(Tile tile);
    bool canPlace(char* direction);
    Tile* getFreeNeighbor(Tile& tile);


private:

    bool tileExists(const std::vector<Tile>& tiles, int x, int y);

    Texture wallTexture;
    Texture floorTexture;
    int maxTiles;
    int gridWidth;
    int gridDepth;

    std::vector<Tile> floorLayout;
    std::vector<Room> rooms;

    bool isInBounds(int x, int y);

};


#endif //OPENGL_DUNGEONGENERATOR_H
