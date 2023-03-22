#include "grid.h"


Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : width(width), height(height), 
                                                                                window(window), mouse(mouse) {
    xTiles = width / tileDim;
    yTiles = height / tileDim;

    totalTiles = xTiles * yTiles;

    // initialize default start tile
    int defaultStartIdx = 0;
    Tile startTile = makeTileFromIdx(defaultStartIdx);
    startTile.setStartTile();

    start = {defaultStartIdx, startTile};

    // initialize default goal tile
    int defaultGoalIdx = totalTiles - 1;
    Tile goalTile = makeTileFromIdx(defaultGoalIdx);
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

    // draw all obstacles
    for (const auto o : obstacles) {
        window.draw(o.second.shape);
    }

    // draw all visited nodes
    for (const auto v : closed) {
        window.draw(v.second.shape);
    }
}

void Grid::addObstacle(void) {
    int tileIdx = getTileIdxFromMousePos();

    if (tileIdx == start.first || tileIdx == goal.first) {
        return;
    }

    if (obstacles.find(tileIdx) == obstacles.end()) {
        Tile obstTile = makeTileFromIdx(tileIdx);
        obstTile.setObstacleTile();

        obstacles[tileIdx] = obstTile;
    }  
}

void Grid::updateStartGoalTiles(void) {
    int tileIdx = getTileIdxFromMousePos();

    if (tileIdx == start.first) {
        setNewTile(true);
    }
    else if (tileIdx == goal.first) {
        setNewTile(false);
    }
}

void Grid::solveAStar(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "starting search" << std::endl;
    std::unordered_map<int, Tile> open;       // open list

    // place start tile in open list with f=0
    open.insert(start);;

    int it = 0;

    // while (!open.empty()) {
    while (it < 5) {
        // print out for open list
        std::cout << " ------- updated open list --------" << std::endl;
        for (auto val : open) {
            std::cout << "tile " << val.first << ", f val " << val.second.f << std::endl;
        }

        // pop q off open list, mark as visited, add to closed list
        auto q = open.begin();
        q->second.setVisited();
        closed.insert(std::make_pair(q->first, q->second));
        open.erase(q);

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        std::cout << "q is " << q->first << std::endl;

        // generate q's successors, add to open list
        auto successors = getSuccessors(q->first, q->second);

        for (auto successor : successors) {
            // if successor is goal, stop search
            if (successor.first == goal.first) {
                std::cout << "goal found!" << std::endl;
                break;
            }

            // calculate g, h and f for each successor
            successor.second.calculateG(start.second);
            successor.second.calculateH(goal.second);
            successor.second.calculateF();

            std::cout << "   successor id " << successor.first << " f value " << successor.second.f << std::endl;

            // if a tile in open has same position as successor
            auto openIt = open.find(successor.first);
            if (openIt != open.end()) {
                std::cout << "   successor found in open list" << std::endl;
                // if tile has lower f than successor, skip
                if (openIt->second.f < successor.second.f) {
                    std::cout << "   successor has larger f value, skipping" << std::endl;
                    continue;
                }
            }

            // if a tile in closed has same position as successor
            auto closedIt = closed.find(successor.first);
            if (closedIt != closed.end()) {
                std::cout << "   successor found in closed list " << std::endl;
                // if tile has lower f than successor, skip
                if (closedIt->second.f < successor.second.f) {
                    std::cout << "   successor has larger f value, skipping" << std::endl;
                    continue;
                }
            }

            // otherwise, add tile to open list
            std::cout << "adding successor " << successor.first << " to open list" << std::endl;

            if (successor.second.f < open.begin()->second.f) {
                std::cout << "successor has smaller f than first value in open map" << std::endl;
                open.insert(open.end(), successor);
            }
            else {
                open.insert(successor);
            }
        }

        std::cout << "++++++ updated closed list ++++++++" << std::endl;
        for (auto c : closed) {
            std::cout << "tile " << c.first << ", f val " << c.second.f << std::endl;
        }

        break;
        it++;
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

Tile Grid::makeTileFromIdx(int idx) {
    int x = idx % xTiles;
    int y = idx / xTiles;
    sf::RectangleShape shape(sf::Vector2f(tileDim, tileDim));
    shape.setPosition(x * tileDim, y * tileDim);
    return Tile(x, y, shape);
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


bool Grid::isInBounds(int x, int y) {
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

void Grid::setNewTile(bool isStart) {
    settingNewTile = true;

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
    Tile newTile = makeTileFromIdx(tileIdx);

    if (isStart == true) {
        newTile.setStartTile();
        start = {tileIdx, newTile};
    }
    else {
        newTile.setGoalTile();
        goal = {tileIdx, newTile};
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
}

std::map<int, Tile> Grid::getSuccessors(int idx, Tile &q) {
    std::vector<std::pair<int, int>> successorPoses;
    
    successorPoses.push_back(std::make_pair(q.x-1, q.y-1));     // north-west
    successorPoses.push_back(std::make_pair(q.x, q.y-1));       // north
    successorPoses.push_back(std::make_pair(q.x+1, q.y-1));       // north-east
    successorPoses.push_back(std::make_pair(q.x+1, q.y));         // east
    successorPoses.push_back(std::make_pair(q.x+1, q.y+1));       // south-east
    successorPoses.push_back(std::make_pair(q.x, q.y+1));         // south
    successorPoses.push_back(std::make_pair(q.x-1, q.y+1));       // south-west
    successorPoses.push_back(std::make_pair(q.x-1, q.y));         // west

    std::map<int, Tile> successors;

    for (auto pos : successorPoses) {
        // check if pos is in bounds
        if (isInBounds(pos.first, pos.second)) {
            // make the tile and add to successors
            int idx = getTileIdxFromTilePos(pos.first, pos.second);
            Tile tile = makeTileFromIdx(idx);
            tile.addParent(idx, q);
            successors.insert({idx, tile});
        }
    }

    return successors;
}
