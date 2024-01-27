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
    struct Tile {
        int x, y;
        bool operator==(const Tile& other) const;
    };

    DungeonGenerator(int maxTiles, int gridWidth, int gridDepth);
    std::vector<Tile> createFloorLayout(std::vector<Mesh*>& sceneMeshes);
    void placeWalls(std::vector<Mesh*>& sceneMeshes);

    void setMaxTiles(int maxTiles);
    void setGridWidth(int gridWidth);
    void setGridDepth(int gridDepth);
    void setFloorLayout(std::vector<Tile> &floorLayout);


private:

    bool tileExists(const std::vector<Tile>& tiles, int x, int y);

    int maxTiles;
    int gridWidth;
    int gridDepth;
    std::vector<Tile> floorLayout;

};


#endif //OPENGL_DUNGEONGENERATOR_H
