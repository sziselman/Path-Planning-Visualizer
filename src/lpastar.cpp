#include "lpastar.h"


LPAStar::LPAStar(Grid* grid) : grid(grid) {}

LPAStar::~LPAStar() {}

void LPAStar::solve(Tile* st, Tile* go) {
    std::cout << "solving search..." << std::endl;
    start = st;
    goal = go;

    if (!isInitialized) {
        initialize();
        isInitialized = true;
    }

    computeShortestPath();
    getPath();
    std::cout << "completed search!\n" << std::endl;
}

void LPAStar::examineChangedTiles() {
    std::cout << "examining changed tiles" << std::endl;
    for (auto tile : grid->getChangedTiles()) {
        std::cout << "tile " << tile->idx << std::endl;
        updatePredecessors(tile);
        updateTile(tile);
    }
}

void LPAStar::initialize() {
    start->rhs = 0.;
    auto keyVal = calculateKey(start);
    start->key = keyVal;
    open.insert(start);
}

void LPAStar::computeShortestPath() {
    auto q = *open.begin();
    while (q->key < calculateKey(goal) || goal->rhs != goal->g) {
        q = *open.begin();
        open.erase(open.begin());
        q->setClosed();
        closed.insert(q->idx);
        if (q->g > q->rhs) {
            q->g = q->rhs;
        }
        else {
            q->g = INT_MAX;
            updateTile(q);
        }
        for (auto successor : grid->getSuccessors(q)) {
            successor->predecessors.insert(q);
            updateTile(successor);
        }

        grid->displayTiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void LPAStar::updateTile(Tile* tile) {
    if (tile != start) {
        tile->rhs = INT_MAX;
        // update the rhs value based on predecessors
        for (auto predecessor : tile->predecessors) {
            tile->rhs = std::min(tile->rhs, calculateG(predecessor, tile));
        }

        auto it = open.find(tile);
        // if priority queue is in open list, remove it
        if (it != open.end()) {
            open.erase(it);
        }
        // if tile is locally inconsistent, put that shit back
        if (tile->g != tile->rhs) {
            // calculate key value and add to open list
            std::pair<double, double> keyVal = calculateKey(tile);
            tile->key = keyVal;
            tile->setOpened();
            open.insert(tile);
        }
    }
}

double LPAStar::calculateH(Tile* tile) {
    double dmax = std::max(abs(goal->x - tile->x), abs(goal->y - tile->y));
    double dmin = std::min(abs(goal->x - tile->x), abs(goal->y - tile->y));
    return cd * dmin + ca * (dmax - dmin);
}

double LPAStar::calculateG(Tile* from, Tile* to) {
    return from->g + sqrt(pow(from->x - to->x, 2) + pow(from->y - to->y, 2));
}

std::pair<double, double> LPAStar::calculateKey(Tile* tile) {
    double k1 = std::min(tile->g, tile->rhs) + calculateH(tile);
    double k2 = std::min(tile->g, tile->rhs);
    return std::make_pair(k1, k2);
}

void LPAStar::getPath() {
    Tile* curr = goal;
    
    std::set<Tile*, AStarTilePtrCompare> preds;
    while (curr != start) {
        curr->setPath();
        preds.clear();
        preds.insert(curr->predecessors.begin(), curr->predecessors.end());
        curr = *preds.begin();
    }
    curr->setPath();
}

void LPAStar::updatePredecessors(Tile* tile) {
    std::vector<Tile*> removePredecessors;

    for (auto p : tile->predecessors) {
        auto obstacles = grid->getObstacles();
        if (obstacles.find(p->idx) != obstacles.end()) {
            removePredecessors.push_back(p);
        }
    }

    for (auto p : removePredecessors) {
        std::cout << "removing predecessor " << p->idx << std::endl;
        tile->predecessors.erase(p);
    }

    std::cout << "updated predecessors" << std::endl;
    for (auto p : tile->predecessors) {
        std::cout << "predecessor tile " << p->idx << std::endl;
    }
}
