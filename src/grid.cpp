#include "grid.h"


Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : window(window), mouse(mouse) {
    xTiles = width / tileDim;
    yTiles = height / tileDim;
    int totalTiles = xTiles * yTiles;

    snakeLen = xTiles / 2;

    Tile* tileptr; 

    for (int i = 0; i < totalTiles; i++) {
        tileptr = makeTileFromIdx(i);
        tileptr->setDefault();
        tileMap[i] = tileptr;
    }

    // initialize default start tile
    start = 0;
    tileMap[start]->setStart();

    // initialize default goal tile
    goal = totalTiles - 1;
    tileMap[goal]->setGoal();
}

Grid::~Grid() {}

Tile* Grid::getStart() {
    return tileMap[start];
}

Tile* Grid::getGoal() {
    return tileMap[goal];
}

void Grid::displayTiles() {
    for (auto t : tileMap) {
        window.draw(t.second->shape);
    }
    window.display();
}

void Grid::addObstacle() {
    int tileIdx = getTileIdxFromMousePos();

    if (tileIdx == start || tileIdx == goal) {
        return;
    }

    if (obstacles.find(tileIdx) == obstacles.end()) {
        obstacles.insert(tileIdx);
        tileMap[tileIdx]->setObstacle();
    }  
}

void Grid::updateStartGoalTiles() {
    int tileIdx = getTileIdxFromMousePos();

    if (tileIdx == start) {
        setNewTile(true);
    }
    else if (tileIdx == goal) {
        setNewTile(false);
    }
}

Tile* Grid::makeTileFromIdx(int idx) {
    int x = idx % xTiles;
    int y = idx / xTiles;
    return new Tile(x, y, idx, tileDim);
}

int Grid::getTileIdxFromMousePos() {
    // determine position and index of tile
    auto pos = mouse.getPosition(window);

    int xTileLoc = ceil(pos.x / tileDim) -1;
    int yTileLoc = ceil(pos.y / tileDim) -1;

    return getTileIdxFromTilePos(std::make_pair(xTileLoc, yTileLoc));
}

int Grid::getTileIdxFromTilePos(std::pair<int, int> pos) {
    return pos.second * xTiles + pos.first;
}

bool Grid::isInBounds(std::pair<int, int> pos) {
    // check if x is in bounds
    bool isXInBounds = (pos.first == std::max(0, std::min(pos.first, xTiles-1)));
    if (isXInBounds == false) {
        return false;
    }
    // check if y is in bounds
    bool isYInBounds = (pos.second == std::max(0, std::min(pos.second, yTiles-1)));
    if (isYInBounds == false) {
        return false;
    }
    return true;
}

void Grid::setNewTile(bool isStart) {
    bool settingNewTile = true;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    int tileIdx;

    while (settingNewTile == true) {
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            tileIdx = getTileIdxFromMousePos();
            
            if (tileIdx != start && tileIdx != goal) {
                if (obstacles.find(tileIdx) == obstacles.end()) {
                    settingNewTile = false;
                }
            }
        }
    }

    if (isStart == true) {
        tileMap[start]->setDefault();

        start = tileIdx;
        tileMap[start]->setStart();
    }
    else {
        tileMap[goal]->setDefault();

        goal = tileIdx;
        tileMap[goal]->setGoal();

    }
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

std::vector<Tile*> Grid::getSuccessors(const Tile* tile) {
    std::vector<std::pair<int, int>> successorPoses;
    
    int x = tile->x;
    int y = tile->y;

    successorPoses.push_back(std::make_pair(x-1, y-1));     // north-west
    successorPoses.push_back(std::make_pair(x, y-1));       // north
    successorPoses.push_back(std::make_pair(x+1, y-1));     // north-east
    successorPoses.push_back(std::make_pair(x+1, y));       // east
    successorPoses.push_back(std::make_pair(x+1, y+1));     // south-east
    successorPoses.push_back(std::make_pair(x, y+1));       // south
    successorPoses.push_back(std::make_pair(x-1, y+1));     // south-west
    successorPoses.push_back(std::make_pair(x-1, y));       // west

    std::vector<Tile*> successors;

    for (auto pos : successorPoses) {
        int idx = getTileIdxFromTilePos(pos);
        if (isInBounds(pos) && obstacles.find(idx) == obstacles.end()) {
            successors.push_back(tileMap[idx]);
        }
    }
    return successors;
}

// void Grid::makeSnakeObstacle() {
//     if (snakeTiles.empty()) {
//         int xmin = 1;
//         int xmax = xTiles - 2;
//         int ymin = 1;
//         int ymax = yTiles - 2;

//         // northern wall
//         for (int i = xmin; i < xmax; i++) {
//             snakeTiles.push_back(getTileIdxFromTilePos(std::make_pair(i, ymin)));
//         }
//         // eastern wall
//         for (int i = ymin; i < ymax; i++) {
//             snakeTiles.push_back(getTileIdxFromTilePos(std::make_pair(xmax, i)));
//         }
//         // southern wall
//         for (int i = xmax; i > xmin; i--) {
//             snakeTiles.push_back(getTileIdxFromTilePos(std::make_pair(i, ymax)));
//         }
//         // western wall
//         for (int i = ymax; i > ymin; i--) {
//             snakeTiles.push_back(getTileIdxFromTilePos(std::make_pair(xmin, i)));
//         }
//     }

//     auto prevObstacles = obstacles;

//     for (auto o : obstacles) {
//         tileMap[o]->setDefault();
//     } 

//     obstacles.clear();

//     snakeTail = (snakeTail + 1) % snakeTiles.size();

//     int val;
//     int idx;
//     for (int s = 0; s < snakeLen; s++) {
//         idx = (snakeTail + s) % snakeTiles.size();
//         val = snakeTiles[idx];
//         obstacles.insert(val);
//     }

//     for (auto o : obstacles) {
//         tileMap[o]->setObstacle();
//     }

//     // find the tiles that changed from obstacle to not or vice versa
//     changedIdxs.clear();
//     auto it = std::set_symmetric_difference(obstacles.begin(), obstacles.end(), prevObstacles.begin(), prevObstacles.end(), std::inserter(changedIdxs, changedIdxs.begin()));
// }

std::set<Tile*> Grid::getChangedTiles() {
    std::set<Tile*> changedTiles;

    for (auto c : changedIdxs) {
        changedTiles.insert(tileMap[c]);
    }
    return changedTiles;
}

std::set<int> Grid::getObstacles() {
    return obstacles;
}

void Grid::makeObstacle(int idx) {
    // clear original obstacles and make copy
    for (auto o : obstacles) {
        tileMap[o]->setDefault();
    }
    auto prevObstacles = obstacles;

    obstacles.clear();

    obstacles.insert(idx);
    // obstacles.insert(idx+1);
    for (auto o : obstacles) {
        tileMap[o]->setObstacle();
    }

    // update the idx of changed tiles
    changedIdxs.clear();
    auto it = std::set_symmetric_difference(obstacles.begin(), obstacles.end(), prevObstacles.begin(), prevObstacles.end(), std::inserter(changedIdxs, changedIdxs.begin()));
}