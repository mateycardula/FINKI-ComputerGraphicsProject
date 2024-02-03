#include <ctime>
#include <iostream>
#include <random>
#include "DungeonGenerator.h"
#include "../Meshes/Factory/Produce/MeshProducer.h"
#include <chrono>
#include <iomanip>


Texture DungeonGenerator::wallTexture;
Texture DungeonGenerator::floorTexture;
float DungeonGenerator::gridSize;
int roomID = -1;


std::string getCurrentTimestamp() {
    // Get current time
    auto now = std::chrono::system_clock::now();

    // Convert to a time_t object
    auto now_time_t = std::chrono::system_clock::to_time_t(now);

    // Convert to tm struct for local timezone
    tm local_tm;
    localtime_s(&local_tm, &now_time_t); // Use localtime_r in Unix-based systems

    // Create a stringstream to format the string
    std::stringstream ss;
    ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S"); // Format: YYYY-MM-DD HH:MM:SS

    return ss.str();
}

// Example of using the function in a log statement
std::string logWithTimestamp(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    auto now_as_time_t = std::chrono::system_clock::to_time_t(now);
    auto local_tm = *std::localtime(&now_as_time_t);

    // Getting milliseconds.
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

    // Constructing the timestamp string.
    std::ostringstream ss;
    ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    ss << '.' << std::setfill('0') << std::setw(3) << milliseconds.count();

    // Add the message.
    ss << " - " << message;

    return ss.str();
}


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
    std::cout<<"TILE MAP SIZE "<<tilesMap.size();
    DungeonGenerator::floorLayout = floorLayout;
}

DungeonGenerator::DungeonGenerator(int maxTiles, int gridWidth, int gridDepth, float gridSize) {
    std::cout<<"Tuka";
    this->maxTiles = maxTiles;
    this->gridWidth = gridWidth;
    this->gridDepth = gridDepth;
    this->floorTexture = Texture("../tex.jpg");
    this->wallTexture = Texture("../t.png");
    this->gridSize = gridSize;

}

std::vector<DungeonGenerator::Tile> DungeonGenerator::createFloorLayout() {
    std::cout<<"TUka";
    int i = 0;
    std::vector<Tile> tiles;
    srand(time(nullptr));


    Tile seed = {gridWidth / 2, gridDepth / 2};
    tiles.push_back(seed);
    addTile(seed.x, seed.y, seed);
    while (tiles.size() < maxTiles) {
        int expandIndex = rand() % tiles.size();
        Tile base = tiles[expandIndex];

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
            addTile(newTile.x, newTile.y, newTile);
        }
    }

    setFloorLayout(tiles);
    return tiles;
}

void DungeonGenerator::placeWalls() {
    for (const auto& tile : floorLayout) {
        bool hasLeftNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x - 1, tile.y}) != floorLayout.end();
        bool hasRightNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x + 1, tile.y}) != floorLayout.end();
        bool hasTopNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x, tile.y - 1}) != floorLayout.end();
        bool hasBottomNeighbor = std::find(floorLayout.begin(), floorLayout.end(), Tile{tile.x, tile.y + 1}) != floorLayout.end();


        glm::vec3 wallColor = glm::vec3(1.0f, 1.0f, 1.0f);
        glm::vec3 wallPosition;
        glm::vec3 wallRotation;

        if (!hasLeftNeighbor) {
            walls.push_back(Wall{glm::vec2(tile.x - 0.5f, tile.y), LEFT});
        }
        if (!hasRightNeighbor) {
            walls.push_back(Wall{glm::vec2 (tile.x+0.5f, tile.y), RIGHT});
        }
        if (!hasTopNeighbor) {
            walls.push_back(Wall{glm::vec2 (tile.x, tile.y - 0.5f), TOP});
        }
        if (!hasBottomNeighbor) {
            walls.push_back(Wall{glm::vec2 (tile.x, tile.y + 0.5f), BOTTOM});
        }
    }

    static const float dx[4] = {0, 0.5f, 0, -0.5f};
    static const float dy[4] = {-0.5f, 0, 0.5f, 0};
    bool placedDoor;
    bool hasNeighbourDoor;
    int j = 0;
    std::ostringstream oss;
    for (const auto& room : rooms) {
        j++;
        std::vector<Wall*> myWalls;
        myWalls.clear();
        std::vector<Wall*> neigbourWalls;
        neigbourWalls.clear();
        placedDoor = false;
        hasNeighbourDoor = false;
        Wall* foundWall;
        for(Tile tile: room.tiles){
            glm::vec2  pos;
            Direction dir;

            for(int i = 0; i<4; i++){
                float wallx = tile.x + dx[i], wallY = tile.y + dy[i];
                pos = {wallx, wallY};
                switch (i) {
                    case 0:
                        dir = TOP;
                        if(std::find(room.tiles.begin(), room.tiles.end(), Tile{tile.x , tile.y - 1}) != room.tiles.end()) {
                            continue;
                        }
                        break;
                    case 1:
                        dir = RIGHT;
                        if(std::find(room.tiles.begin(), room.tiles.end(), Tile{tile.x + 1, tile.y}) != room.tiles.end()) {
                            continue;
                        }
                        break;
                    case 2:
                        dir = BOTTOM;
                        if(std::find(room.tiles.begin(), room.tiles.end(), Tile{tile.x, tile.y + 1}) != room.tiles.end()) {
                            continue;
                        }
                        break;
                    case 3:
                        dir = LEFT;

                        if(std::find(room.tiles.begin(), room.tiles.end(), Tile{tile.x - 1, tile.y}) != room.tiles.end()) {
                            continue;
                        }
                        break;
                }

                foundWall = findWall(pos);
                if(foundWall == nullptr){
                    Wall* newWall = new Wall{pos, dir};
                    newWall->isInnerWall = true;
                    if(rand()%100 < 2){
                        newWall->isDoorWay = true;
                        placedDoor = true;
                    }
                    myWalls.push_back(newWall);
                }
                else{
                    if(foundWall->isInnerWall)
                        neigbourWalls.push_back(foundWall);
                    if(foundWall->isDoorWay) {
                        hasNeighbourDoor = true;
                    }
                }
            }

        }

        if(!placedDoor && !myWalls.empty()){
            std::cout<<logWithTimestamp(" PLACING A DOORWAY "  + std::to_string(j))<<std::endl<<std::flush;
            size_t index = static_cast<size_t>(rand()) % myWalls.size();
            myWalls.at(index)->isDoorWay = true;
        }

        if(!hasNeighbourDoor && !neigbourWalls.empty()){
            std::cout<<logWithTimestamp("PLACING NEIGHBOURDOOR, AS THERE IS NO CONNECTION TO A NEIGHBOUR " + std::to_string(j))<<std::endl<<std::flush;
            size_t index = static_cast<size_t>(rand()) % neigbourWalls.size();
            neigbourWalls.at(index)->isDoorWay = true;
        }

        for(Wall* wall : myWalls){
            walls.push_back(*wall);
        }

        std::cout<<myWalls.size()<<std::endl;
        std::cout<<"NEIGHBOURS "<<neigbourWalls.size()<<std::endl;
    }
    std::cout<<"WALLS: "<<walls.size();

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
    std::cout<<"FLOORS: "<<floorLayout.size();

    std::random_device rd;
    std::mt19937 gen(rd());


    std::uniform_real_distribution<> dis(0.0, 1.0);
    std::uniform_real_distribution<> y_dis(-1.0, 4.0);


    for (const auto& pair : tilesMap){
        Tile* floorTile = findTile(pair.first.first, pair.first.second);
        if(floorTile->roomID==-1){
            roomID++;
            floorTile->roomID = roomID;

            glm::vec3 roomColor = {dis(gen), dis(gen), dis(gen)};
            expandRoom(floorTile, roomColor);

        }
    }
//    for(Tile& floorTile : floorLayout){
//        if(!isRoomTIle(floorTile)){
//            if(rand() % 100 < 20){
//                Room room;
//                room.color = glm::vec3(dis(gen), dis(gen), dis(gen));
//                room.y_val = y_dis(gen);
//                room.tiles.push_back(floorTile);
//                expandRoom(room, sceneMeshes);
//                rooms.push_back(room);
//            }
//        }
//    }
}


bool DungeonGenerator::isRoomTIle(DungeonGenerator::Tile tile) {
    for(auto& room : DungeonGenerator::rooms){
        for(Tile roomTile : room.tiles){
            if(tile == roomTile) {
                return true; }
        }
    }
    return false;
}

void DungeonGenerator::expandRoom(Tile* root, glm::vec3 roomColor){
    int i = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> y_dis(-1.0, 4.0);
    root->color = roomColor;

    Tile inspectingTile = *root;
    while(true){
        if(rand() % 100 < 100 - i){
            Tile* newTile(getFreeNeighbor(inspectingTile.x, inspectingTile.y));
            if(newTile != nullptr){
                newTile->roomID = roomID;
                newTile->color = roomColor;
                inspectingTile = *newTile;
                i++;
            }
            else{
                return;
            }

        }
        else return;
    }


    //    Tile inspectingTile = room.tiles.at(0);
//    bool loop = true;
//    while(loop){
//        inspectingTile.color = room.color;
//        if(rand() % 100 < 90){
//            std::unique_ptr<Tile> newTile(getFreeNeighbor(inspectingTile));
//            if(newTile != nullptr){
//                room.tiles.push_back(*newTile);
//                inspectingTile = *newTile;
//            }
//            else{
//                return;
//            }
//        }
//        else{
//            return;
//        }
//    }


}

bool DungeonGenerator::isInBounds(int x, int y) {
    Tile inspectingTile = Tile{x, y};
    for(Tile floor: floorLayout){
        if(inspectingTile == floor) return true;
    }
    return false;
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

DungeonGenerator::Wall* DungeonGenerator::findWall(glm::vec2 position) {
    Wall cmp{position};
    for(Wall& wall : walls){
        if(wall == cmp) {
            return &wall;
        }
    }
    return nullptr;
}

void DungeonGenerator::fetchFloorMeshes(std::vector<Mesh *> &sceneMeshes) {
    for (const auto& pair : tilesMap){
        int x = pair.first.first;
        int z = pair.first.second;
        Tile tile = pair.second;

        sceneMeshes.push_back(MeshProducer()
                                      .withColor(tile.color)
                                      .atPosition(glm::vec3(x * 3.0f - (gridWidth/2)*3 , -2.0f, z * 3.0f - (gridDepth/2)*3))
                                      .withTexture(floorTexture)
                                      .CreateFloor(gridSize));
    }
}

void DungeonGenerator::fetchOuterWallMeshes(std::vector<Mesh *> &sceneMeshes) {
    glm::vec3 wallRotation;

    for(Wall wall : walls){
        float actualX = wall.position.x * 3.0f - (gridWidth/2)*3;
        float actualZ = wall.position.y * 3.0f - (gridDepth/2)*3;
        if(wall.isDoorWay) wall.color = {0.5f, 1.0f, 0.2f};
        switch (wall.dir) {
            case LEFT:
                wallRotation = wall.leftRotation;
                break;
            case RIGHT:
                wallRotation = wall.rightRotation;
                break;
            case TOP:
                wallRotation = wall.topRotation;
                break;
            case BOTTOM:
                wallRotation = wall.bottomRotation;
                break;
        }

        sceneMeshes.push_back(MeshProducer()
                                      .withColor(wall.color)
                                      .withRotation(wallRotation)
                                      .atPosition(glm::vec3(actualX , -0.5f, actualZ))
                                      .withTexture(wallTexture)
                                      .CreateWall(gridSize));
    }

}


bool DungeonGenerator::Wall::operator==(const DungeonGenerator::Wall &other) const {
    return position.x == other.position.x && position.y == other.position.y;
}