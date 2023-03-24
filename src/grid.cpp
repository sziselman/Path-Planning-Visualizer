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
    std::this_thread::sleep_for(std::chrono::milliseconds(60));

    std::set<Tile*, TilePtrCompare> open;

    // add the start tile to the map, add to open list
    tileMap.insert(start);
    open.insert(start.second);

    while (!open.empty()) {
        displayVisitedTiles();

        auto q = *open.begin();
        q->setVisited();
        closed.insert(q->idx);
        open.erase(open.begin());
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        for (auto p : path) {
            tileMap[p]->setVisited();
        }
        path.clear();
        getTraversedPath(q->idx);
        displayPathTiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        if (q->idx == goal.first) {
            break;
        }
        for (auto successor : getSuccessors(q)) {
            if (tileMap.find(successor->idx) != tileMap.end()) {
                if (closed.find(successor->idx) == closed.end()) {
                    if (tileMap[successor->idx]->f > successor->f) {
                        // update f value and parent
                        tileMap[successor->idx]->parent = q;
                        tileMap[successor->idx]->f = successor->f;
                        tileMap[successor->idx]->g = successor->g;
                    }
                }
            }
            else {
                open.insert(successor);
                tileMap.insert({successor->idx, successor});
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
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

    return getTileIdxFromTilePos(std::make_pair(xTileLoc, yTileLoc));
}

int Grid::getTileIdxFromTilePos(std::pair<int, int> pos) {
    return pos.second * xTiles + pos.first;
}

bool Grid::isInBounds(std::pair<int, int> pos) {
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
        start = std::make_pair(tileIdx, newTile);
    }
    else {
        newTile->setGoalTile();
        goal = std::make_pair(tileIdx, newTile);
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
    for (auto p : path) {
        tileMap[p]->setPath();
        window.draw(tileMap[p]->shape);
    }
    window.display();
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
    successorPoses.push_back(std::make_pair(x+1, y-1));     // south-west
    successorPoses.push_back(std::make_pair(x-1, y));       // west

    std::vector<Tile*> successors;

    for (auto pos : successorPoses) {
        int idx = getTileIdxFromTilePos(pos);
        if (isInBounds(pos) && obstacles.find(idx) == obstacles.end()) {
            Tile* newTile = makeTileFromIdx(idx);
            newTile->parent = tile;
            newTile->calculateF(goal.second);
            successors.push_back(newTile);
        }
    }
    return successors;
}

void Grid::getTraversedPath(int idx) {
    path = {idx};
    int parentIdx;
    while (tileMap[idx]->parent != nullptr) {
        parentIdx = tileMap[idx]->parent->idx;
        path.insert(path.begin(), parentIdx);
        idx = parentIdx;
    }
}
