#include "grid.h"


Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : width(width), height(height), 
                                                                                window(window), mouse(mouse) {
    xTiles = width / tileDim;
    yTiles = height / tileDim;

    totalTiles = xTiles * yTiles;

    // initialize default start tile
    int defaultStartIdx = 0;
    int defaultStartX = defaultStartIdx % xTiles;
    int defaultStartY = defaultStartIdx / xTiles;
    sf::RectangleShape startShape(sf::Vector2f(tileDim, tileDim));
    startShape.setPosition(defaultStartX * tileDim, defaultStartY * tileDim);
    Tile startTile(defaultStartX, defaultStartY, startShape);
    startTile.setStartTile();

    start = {defaultStartIdx, startTile};

    // initialize default goal tile
    int defaultGoalIdx = totalTiles - 1;
    int defaultGoalX = defaultGoalIdx % xTiles;
    int defaultGoalY = defaultGoalIdx / xTiles;
    sf::RectangleShape goalShape(sf::Vector2f(tileDim, tileDim));
    goalShape.setPosition(defaultGoalX * tileDim, defaultGoalY * tileDim);
    Tile goalTile(defaultGoalX, defaultGoalY, goalShape);
    goalTile.setGoalTile();

    goal = {defaultGoalIdx, goalTile};
}

Grid::~Grid() {}

void Grid::displayDefaultGrid(void) {
    // set visualization for tiles
    for (int i = 0; i < totalTiles; i++) {
        sf::RectangleShape shape(sf::Vector2f(tileDim, tileDim));
        
        double x = (i % xTiles) * tileDim;
        double y = (i / xTiles) * tileDim;

        shape.setFillColor(openTileColor);
        shape.setOutlineColor(outlineTileColor);
        shape.setOutlineThickness(outlineTileThickness);
        shape.setPosition(x, y);
        window.draw(shape);
    }
}

void Grid::displayTiles(void) {
    window.draw(start.second.shape);
    window.draw(goal.second.shape);

    for (const auto o : obstacles) {
        window.draw(o.second.shape);
    }
}

void Grid::addObstacle(void) {
    // TODO : add check to avoid making start/end tiles obstacles
    int tileIdx = getTileIdxFromMousePos();

    if (obstacles.find(tileIdx) == obstacles.end()) {
        int x = tileIdx % xTiles;
        int y = tileIdx / xTiles;

        sf::RectangleShape obstShape(sf::Vector2f(tileDim, tileDim));
        obstShape.setPosition(x * tileDim, y * tileDim);

        Tile obstTile(x, y, obstShape);
        obstTile.setObstacleTile();

        obstacles[tileIdx] = obstTile;
    }  
}

void Grid::updateStartGoalTiles(void) {
    int tileIdx = getTileIdxFromMousePos();

    // check if tile is start, goal, obstacle or neither
    if (tileIdx == start.first) {
        std::cout << "setting new start tile" << std::endl;
        // setStartTile();
    }
    else if (tileIdx == goal.first) {
        std::cout << "setting new goal tile" << std::endl;
        // setGoalTile();
    }
    else if (obstacles.find(tileIdx) != obstacles.end()) {
        std::cout << "can't make an obstacle a start/goal tile" << std::endl;
        return;
    }
    else {
        startSearch();
    }
    return;
}

void Grid::solveAStar(void) {
    return;
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

void Grid::setStartTile(void) {
    // settingNewStart = true;

    // std::this_thread::sleep_for(std::chrono::milliseconds(300));

    // int tileIdx;

    // while (settingNewStart == true) {
    //     if (mouse.isButtonPressed(sf::Mouse::Left)) {
    //         tileIdx = getTileIdxFromMousePos();
    //         settingNewStart = false;
    //     }
    // }

    // // check if tile is start, obstacle, or goal
    // if (tileMap[tileIdx].isStart == true || tileMap[tileIdx].isGoal == true || tileMap[tileIdx].isObstacle == true) {
    //     std::cout << "already is start, goal, or obstacle tile" << std::endl;
    //     return;
    // } 
    // else {
    //     // update start tile info
    //     tileMap[startTileIdx].setDefaultTile();
    //     tileMap[tileIdx].setStartTile();
    //     startTileIdx = tileIdx;
    // }

    // std::this_thread::sleep_for(std::chrono::milliseconds(300));

    return;
}

void Grid::setGoalTile(void) {
    // settingNewGoal = true;
    // std::this_thread::sleep_for(std::chrono::milliseconds(200));

    // int tileIdx;

    // while (settingNewGoal == true) {
    //     if (mouse.isButtonPressed(sf::Mouse::Left)) {
    //         tileIdx = getTileIdxFromMousePos();
    //         settingNewGoal = false;
    //     }
    // }

    // // check if tile is start, obstacle, or goal
    // if (tileMap[tileIdx].isStart == true || tileMap[tileIdx].isGoal == true || tileMap[tileIdx].isObstacle == true) {
    //     std::cout << "already is start, goal, or obstacle tile" << std::endl;
    //     return;
    // } 
    // else {
    //     // update start tile info
    //     tileMap[goalTileIdx].setDefaultTile();
    //     tileMap[tileIdx].setGoalTile();
    //     goalTileIdx = tileIdx;
    // }

    // std::this_thread::sleep_for(std::chrono::milliseconds(200));
    return;
}

void Grid::startSearch(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
