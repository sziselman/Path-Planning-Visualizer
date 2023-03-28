#include "grid.h"


Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : window(window), mouse(mouse) {
    xTiles = width / tileDim;
    yTiles = height / tileDim;
    int totalTiles = xTiles * yTiles;

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

void Grid::solveAStar() {
    std::set<int> closed;
    std::set<Tile*, AStarTilePtrCompare> open;

    tileMap[start]->updateG(0.);
    tileMap[start]->updateF(0.);
    open.insert(tileMap[start]);

    double g, h, f;
    while (!open.empty()) {

        auto q = *open.begin();
        q->setClosed();
        closed.insert(q->idx);
        open.erase(open.begin());
        displayTiles();

        if (q->idx == goal) {
            break;
        }

        for (auto successor : getSuccessors(q->idx)) {

            if (closed.find(successor) != closed.end()) {
                continue;
            }
    
            g = tileMap[successor]->calculateG(q);
            h = tileMap[successor]->calculateH(tileMap[goal]);
            f = g + h;

            auto it = open.find(tileMap[successor]);
            if (it != open.end()) {
                if (tileMap[successor]->f > f) {
                    open.erase(it);
                    tileMap[successor]->updateParent(q);
                    tileMap[successor]->updateF(f);
                    open.insert(tileMap[successor]);
                }
            }
            else {
                tileMap[successor]->updateParent(q);
                tileMap[successor]->updateF(f);
                tileMap[successor]->setOpened();
                open.insert(tileMap[successor]);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    getPath();
}

void Grid::solveLPAStar() {
    std::set<int> closed;
    std::set<Tile*, LPAStarTilePtrCompare> pq;

    tileMap[start]->rhs = 0.;
    auto key = tileMap[start]->calculateKeys(tileMap[goal]);
    tileMap[start]->key = key;
    pq.insert(tileMap[start]);

    auto q = *pq.begin();
    int i = 0;
    while (i < 5) {
    // while (q->key < tileMap[goal]->calculateKeys(tileMap[goal]) || tileMap[goal]->rhs != tileMap[goal]->g) {
        std::cout << "++++ priority queue ++++" << std::endl;
        for (auto qu : pq) {
            std::cout << "  tile " << qu->idx << ", address " << qu << ", key {" << qu->key.first << ", " << qu->key.second << "}" << std::endl;
        }
        auto q = *pq.begin();
        pq.erase(pq.begin());

        std::cout << "q is " << q->idx << ", address " << q << std::endl;
        if (q->g > q->rhs) {
            q->updateG(q->rhs);
            std::cout << "  updating g to rhs value " << q->g << std::endl;
        }
        else {
            q->updateG(INT_MAX);
        //     if (q->idx != start) {
        //         for (int successor : getSuccessors(q->idx)) {
        //             q->rhs = std::min(q->rhs, tileMap[successor]->g + tileMap[successor]->calculateH(tileMap[goal]));
        //             if (q->g != q->rhs) {
        //                 pq.insert(q);
        //             }
        //         }
        //     }
        }
        // q = *pq.begin();

        i++;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(100)); 
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

    std::vector<int> successors;

    for (auto pos : successorPoses) {
        int idx = getTileIdxFromTilePos(pos);
        if (isInBounds(pos) && obstacles.find(idx) == obstacles.end()) {
            successors.push_back(idx);
        }
    }
    return successors;
}

void Grid::getPath() {
    int idx = goal;
    int parentIdx;
    while (tileMap[idx]->parent != nullptr) {
        tileMap[idx]->setPath();
        idx = tileMap[idx]->parent->idx;
    }
    tileMap[idx]->setPath();
}