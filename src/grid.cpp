#include "grid.h"


Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : width(width), height(height), 
                                                                                window(window), mouse(mouse) {
    xTiles = width / tileDim;
    yTiles = height / tileDim;
    totalTiles = xTiles * yTiles;

    // initialize default start tile
    int defaultStartIdx = 0;
    Tile* startTile = makeTileFromIdx(defaultStartIdx);
    startTile->setStartTile();

    start = {defaultStartIdx, startTile};

    // initialize default goal tile
    int defaultGoalIdx = totalTiles - 1;
    Tile* goalTile = makeTileFromIdx(defaultGoalIdx);
    goalTile->setGoalTile();

    goal = {defaultGoalIdx, goalTile};
}

Grid::~Grid() {}

void Grid::displayDefaultGrid() {
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

void Grid::displayTiles() {
    window.draw(start.second->shape);
    window.draw(goal.second->shape);

    for (const int obst : obstacles) {
        window.draw(tileMap[obst]->shape);
    }

    displayVisitedTiles();
}

void Grid::addObstacle() {
    int tileIdx = getTileIdxFromMousePos();

    if (tileIdx == start.first || tileIdx == goal.first) {
        return;
    }

    if (obstacles.find(tileIdx) == obstacles.end()) {
        // add obstacle index to obstacles
        obstacles.insert(tileIdx);

        // make tile and add to tile map
        Tile* obstTile = makeTileFromIdx(tileIdx);
        obstTile->setObstacleTile();
        tileMap[tileIdx] = obstTile;
    }  
}

void Grid::updateStartGoalTiles() {
    int tileIdx = getTileIdxFromMousePos();

    if (tileIdx == start.first) {
        setNewTile(true);
    }
    else if (tileIdx == goal.first) {
        setNewTile(false);
    }
}

void Grid::solveAStar() {
    std::cout << "starting search" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    std::set<Tile*, TilePtrCompare> open;

    // place start tile in open list with f=0
    open.insert(start.second);

    while (!open.empty()) {

        displayVisitedTiles();

        // pop q off open list, mark as visited, add to tile map, add to closed list
        auto q = *open.begin();

        // draw traversed path
        getTraversedPath(q->idx);
        displayPathTiles();

        q->setVisited();
        tileMap.insert({q->idx, q});
        closed.insert(q->idx);
        open.erase(q);

        // check if q is the goal, if so end
        if (q->idx == goal.first) {
            break;
        }

        // generate q's successors, add to open list
        std::vector<int> successors = getSuccessors(q->idx);

        for (auto successorIdx : successors) {
            // make a tile for the successor
            Tile* successorTile = makeTileFromIdx(successorIdx);
            // mark it's parent
            successorTile->parent = q;

            // calculate g, h and f for each successor
            successorTile->calculateG();
            successorTile->calculateH(goal.second);
            successorTile->calculateF();

            if (tileMap.find(successorIdx) != tileMap.end()) {
                if (closed.find(successorIdx) == closed.end()) {
                    if (tileMap[successorIdx]->f > successorTile->f) {
                        tileMap[successorIdx]->f = successorTile->f;
                    }
                }
            }
            else {
                open.insert(successorTile);
                tileMap.insert({successorIdx, successorTile});
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

Tile* Grid::makeTileFromIdx(int idx) {
    int x = idx % xTiles;
    int y = idx / xTiles;
    sf::RectangleShape shape(sf::Vector2f(tileDim, tileDim));
    shape.setPosition(x * tileDim, y * tileDim);
    return new Tile(x, y, idx, shape);
}

int Grid::getTileIdxFromMousePos() {
    // determine position and index of tile
    auto pos = mouse.getPosition(window);

    int xTileLoc = ceil(pos.x / tileDim) -1;
    int yTileLoc = ceil(pos.y / tileDim) -1;

    return getTileIdxFromTilePos(xTileLoc, yTileLoc);
}

int Grid::getTileIdxFromTilePos(int x, int y) {
    return y * xTiles + x;
}

bool Grid::isInBounds(int x, int y) {
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

void Grid::setNewTile(bool isStart) {
    bool settingNewTile = true;

    std::this_thread::sleep_for(std::chrono::milliseconds(300));

    int tileIdx;

    while (settingNewTile == true) {
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            tileIdx = getTileIdxFromMousePos();
            
            if (tileIdx != start.first && tileIdx != goal.first) {
                if (obstacles.find(tileIdx) == obstacles.end()) {
                    std::cout << "selected new start tile that is neither previous start, goal, or obstacle" << std::endl;
                    settingNewTile = false;
                }
            }
        }
    }

    // update start tile info
    Tile* newTile = makeTileFromIdx(tileIdx);

    if (isStart == true) {
        newTile->setStartTile();
        start = {tileIdx, newTile};
    }
    else {
        newTile->setGoalTile();
        goal = {tileIdx, newTile};
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

void Grid::displayVisitedTiles() {
    for (int clo : closed) {
        window.draw(tileMap[clo]->shape);   
    }
    window.display();
}

void Grid::displayPathTiles() {
    for (auto pa : path) {
        std::cout << pa << std::endl;
    //     window.draw(tileMap[pa]->shape);
    }
    window.display();
}

std::vector<int> Grid::getSuccessors(int idx) {
    std::vector<std::pair<int, int>> successorPoses;
    
    int x = tileMap[idx]->x;
    int y = tileMap[idx]->y;

    successorPoses.push_back(std::make_pair(x-1, y-1));     // north-west
    successorPoses.push_back(std::make_pair(x, y-1));       // north
    successorPoses.push_back(std::make_pair(x+1, y-1));     // north-east
    successorPoses.push_back(std::make_pair(x+1, y));       // east
    successorPoses.push_back(std::make_pair(x+1, y+1));     // south-east
    successorPoses.push_back(std::make_pair(x, y+1));       // south
    successorPoses.push_back(std::make_pair(x-1, y+1));     // south-west
    successorPoses.push_back(std::make_pair(x-1, y));       // west

    std::vector<int> successorIdxs;

    for (auto pos : successorPoses) {
        // check if pos is in bounds
        if (isInBounds(pos.first, pos.second)) {
            // make the tile and add to successors
            int idx = getTileIdxFromTilePos(pos.first, pos.second);

            // check if tile index is in obstacles 
            if (obstacles.find(idx) == obstacles.end()) {
                successorIdxs.push_back(idx);
            }
        }
    }
    return successorIdxs;
}

void Grid::getTraversedPath(int idx) {
    return;
}
