#include "lpastar.h"


LPAStar::LPAStar(Grid& grid) : grid(grid) {}

void LPAStar::solve(Tile* st, Tile* go) {
    std::cout << "solving search..." << std::endl;
    start = st;
    goal = go;

    initialize();
    computeShortestPath();
    getPath();
    std::cout << "completed search!\n" << std::endl;
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

        std::cout << "\n\n\n++++ updated priority queue ++++" << std::endl;
        for (auto o : open) {
            std::cout << "   tile " << o->idx << ", g=" << o->g << ", k1=" << o->key.first << ", k2=" << o->key.second << std::endl;
        }


        q = *open.begin();
        open.erase(open.begin());
        q->setClosed();
        closed.insert(q->idx);

        std::cout << "\n\nq is " << q->idx << ", g=" << q->g << ", rhs=" << q->rhs << std::endl;
        std::cout << "k1=" << q->key.first << ", k2=" << q->key.second << std::endl;

        std::cout << "\n\ngoal k1=" << goal->key.first << ", k2=" << goal->key.second << std::endl;

        if (q->g > q->rhs) {
            q->g = q->rhs;
            std::cout << "q's g updated to " << q->g << std::endl;
        }
        else {
            q->g = INT_MAX;
            updateTile(q);
        }

        std::cout << "\nSEARCHING SUCCESSORS: " << std::endl;
        for (auto successor : grid.getSuccessors(q->idx)) {
            successor->predecessors.insert(q);
            updateTile(successor);
        }

        grid.displayTiles();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void LPAStar::updateTile(Tile* tile) {
    std::cout << "  updating tile " << tile->idx << std::endl;

    if (tile != start) {
        tile->rhs = INT_MAX;


        std::cout << "  searching predecessors to update rhs" << std::endl;
        // update the rhs value based on predecessors
        for (auto predecessor : tile->predecessors) {
            tile->rhs = std::min(tile->rhs, calculateG(predecessor, tile));
            std::cout << "  tile " << tile->idx << ", rhs=" << tile->rhs << std::endl;
        }

        auto it = open.find(tile);
        // if priority queue is in open list, remove it
        if (it != open.end()) {
            std::cout << "  removing from priority queue" << std::endl;
            open.erase(it);
        }
        // if tile is locally inconsistent, put that shit back
        if (tile->g != tile->rhs) {
            std::cout << "  locally inconsistent, adding to priority queue" << std::endl;
            std::cout << "  g=" << tile->g << ", rhs=" << tile->rhs << std::endl;
            // calculate key value and add to open list
            std::pair<double, double> keyVal = calculateKey(tile);
            tile->key = keyVal;
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
