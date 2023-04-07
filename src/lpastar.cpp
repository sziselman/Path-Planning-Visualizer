#include "lpastar.h"


LPAStar::LPAStar(Grid& grid): grid(grid) {}

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

    auto obstacles = grid.getObstacles();

    bool isObstacle;

    std::cout << "\n\n ~~~~ examining changed tiles ~~~~" << std::endl;
    for (auto tile : grid.getChangedTiles()) {
        std::cout << "\n\ntile " << tile->idx << std::endl;
        for (auto successor : grid.getSuccessors(tile)) {
            if (obstacles.find(tile->idx) != obstacles.end()) {
                successor->predecessors.erase(tile);
            }
            else {
                successor->predecessors.insert(tile);
            }
            updateTile(successor);
        }
    }

    std::cout << "\n ++++ updated priority queue ++++" << std::endl;
    for (auto o : open) {
        std::cout << "tile " << o->idx << ", address=" << o << ", k1=" << o->key.first << ", k2=" << o->key.second << ", g=" << o->g << ", rhs=" << o->rhs << std::endl;
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

        std::cout << "\n ++++ updated priority queue ++++" << std::endl;
        for (auto o : open) {
            std::cout << "tile " << o->idx << ", address=" << o << ", k1=" << o->key.first << ", k2=" << o->key.second << std::endl;
        }

        q = *open.begin();
        open.erase(open.begin());
        q->setClosed();
        closed.insert(q->idx);

        std::cout << "\nq is " << q->idx << std::endl;

        if (q->g > q->rhs) {
            q->g = q->rhs;
        }
        else {
            q->g = INT_MAX;
            updateTile(q);
        }

        std::cout << "q's successors: " << std::endl;
        for (auto successor : grid.getSuccessors(q)) {
            std::cout << "  tile " << successor->idx << std::endl;
            successor->predecessors.insert(q);
            updateTile(successor);
        }

        grid.displayTiles();

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void LPAStar::updateTile(Tile* tile) {
    std::cout << "updating tile " << tile->idx << ", rhs=" << tile->rhs << ", g=" << tile->g << std::endl;
    if (tile != start) {
        tile->rhs = INT_MAX;
        // update the rhs value based on predecessors
        for (auto predecessor : tile->predecessors) {
            std::cout << "   predecessor tile " << predecessor->idx << std::endl;
            tile->rhs = std::min(tile->rhs, calculateG(predecessor, tile));
        }
        std::cout << "   updated rhs value " << tile->rhs << ", g=" << tile->g << std::endl;

        auto it = open.find(tile);
        // if priority queue is in open list, remove it
        if (it != open.end()) {
            open.erase(it);
        }

        // if tile is locally inconsistent, put that shit back
        if (tile->g != tile->rhs) {
            // calculate key value and add to open list
            std::pair<double, double> keyVal = calculateKey(tile);
            std::cout << "  key 1=" << keyVal.first << ", k2=" << keyVal.second << std::endl;
            tile->key = keyVal;
            // tile->setOpened();
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

void LPAStar::examineTile(Tile* tile) {
    std::cout << "successors " << std::endl;
    for (auto successor : grid.getSuccessors(tile)) {
        std::cout << "  tile " << successor->idx << std::endl;

        if (successor->predecessors.find(tile) != successor->predecessors.end()) {
            successor->predecessors.erase(tile);
        }
    }
}
