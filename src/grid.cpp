#include "grid.h"


Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : width(width), height(height), 
                                                                                window(window), mouse(mouse) {
    xTiles = width / tileDim;
    yTiles = height / tileDim;

    totalTiles = xTiles * yTiles;

    // add tiles to map
    for (int i = 0; i < totalTiles; i++) {
        sf::RectangleShape shape(sf::Vector2f(tileDim, tileDim));
        int x = i % xTiles;
        int y = i / xTiles;

        tileMap.push_back(Tile(x, y, i, shape));
    }

    // set properties of each tile in map, update neighbors
    for (int i = 0; i < totalTiles; i++) {
        double x_loc = double(tileMap[i].x * tileDim);
        double y_loc = double(tileMap[i].y * tileDim);

        tileMap[i].updateNeighbors(getNeighborsFromTilePos(tileMap[i].x, tileMap[i].y));

        tileMap[i].shape.setPosition(x_loc, y_loc);
        tileMap[i].setDefaultTile();
    }

    // set the start, goal positions
    startTileIdx = 0;
    tileMap[startTileIdx].setStartTile();

    goalTileIdx = tileMap.size()-1;
    tileMap[goalTileIdx].setGoalTile();
}

Grid::~Grid() {}

void Grid::displayGrid(void) {
    for (auto tile : tileMap) {
        window.draw(tile.shape);
    }
}

int Grid::getTileIdxFromMousePos(void) {
    // determine position and index of tile
    auto pos = mouse.getPosition(window);

    int xTileLoc = ceil(pos.x / tileDim) -1;
    int yTileLoc = ceil(pos.y / tileDim) -1;

    return getTileIdxFromTilePos(xTileLoc, yTileLoc);
}

int Grid::getTileIdxFromTilePos(int x, int y) {
    return y * xTiles + x;
}

std::vector<std::pair<int, int>> Grid::getNeighborIdxsFromTilePos(int x, int y) {
    std::vector<std::pair<int, int>> neighborIdxs;

    neighborIdxs.push_back(std::make_pair(x-1, y-1));   // north-west
    neighborIdxs.push_back(std::make_pair(x, y-1));     // north
    neighborIdxs.push_back(std::make_pair(x+1, y-1));   // north-east
    neighborIdxs.push_back(std::make_pair(x+1, y));     // east
    neighborIdxs.push_back(std::make_pair(x+1, y+1));   // south-east
    neighborIdxs.push_back(std::make_pair(x, y+1));     // south
    neighborIdxs.push_back(std::make_pair(x-1, y+1));   // south-west
    neighborIdxs.push_back(std::make_pair(x-1, y));     // west

    return neighborIdxs;
}

std::vector<int> Grid::getNeighborsFromTilePos(int x, int y) {
    std::vector<int> neighbors;

    // loop through pairs, if in bounds add to list of neighbors
    for (auto idxPair : getNeighborIdxsFromTilePos(x, y)) {
        if (isOutOfBounds(idxPair.first, idxPair.second) != false) {
            neighbors.push_back(getTileIdxFromTilePos(idxPair.first, idxPair.second));
        }
    }

    return neighbors;
}

bool Grid::isOutOfBounds(int x, int y) {
    // check if x is in bounds
    bool isXInBounds = (x == std::max(0, std::min(x, xTiles-1)));
    if (isXInBounds == false) {
        return false;
    }
    // check if y is in bounds
    bool isYInBounds = (y == std::max(0, std::min(y, yTiles-1)));
    if (isYInBounds == false) {
        return false;
    }
    return true;
}

void Grid::addObstacle(void) {
    int tileIdx = getTileIdxFromMousePos();

    // check if tile is start or goal
    if (tileMap[tileIdx].isStart == true || tileMap[tileIdx].isGoal == true) {
        return;
    }
    else {
        tileMap[tileIdx].setObstacleTile();
        obstacleMap.push_back(tileMap[tileIdx]);
    }
}

void Grid::updateGrid(void) {
    int tileIdx = getTileIdxFromMousePos();

    // check if tile is start, goal, obstacle or neither
    if (tileMap[tileIdx].isStart == true) {
        std::cout << "setting new start tile" << std::endl;
        setStartTile();
    }
    else if (tileMap[tileIdx].isGoal == true) {
        setGoalTile();
    }
    else if (tileMap[tileIdx].isObstacle == true) {
        return;
    }
    else {
        startSearch();
    }
}

void Grid::setStartTile(void) {
    settingNewStart = true;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    int tileIdx;

    while (settingNewStart == true) {
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            tileIdx = getTileIdxFromMousePos();
            settingNewStart = false;
        }
    }

    // check if tile is start, obstacle, or goal
    if (tileMap[tileIdx].isStart == true || tileMap[tileIdx].isGoal == true || tileMap[tileIdx].isObstacle == true) {
        std::cout << "already is start, goal, or obstacle tile" << std::endl;
        return;
    } 
    else {
        // update start tile info
        tileMap[startTileIdx].setDefaultTile();
        tileMap[tileIdx].setStartTile();
        startTileIdx = tileIdx;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void Grid::setGoalTile(void) {
    settingNewGoal = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    int tileIdx;

    while (settingNewGoal == true) {
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            tileIdx = getTileIdxFromMousePos();
            settingNewGoal = false;
        }
    }

    // check if tile is start, obstacle, or goal
    if (tileMap[tileIdx].isStart == true || tileMap[tileIdx].isGoal == true || tileMap[tileIdx].isObstacle == true) {
        std::cout << "already is start, goal, or obstacle tile" << std::endl;
        return;
    } 
    else {
        // update start tile info
        tileMap[goalTileIdx].setDefaultTile();
        tileMap[tileIdx].setGoalTile();
        goalTileIdx = tileIdx;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}

void Grid::startSearch(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
