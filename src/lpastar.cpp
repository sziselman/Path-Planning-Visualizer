#include "lpastar.h"


LPAStar::LPAStar(Grid* grid) : grid(grid) {}

void LPAStar::solve(Tile* st, Tile* go) {
    std::cout << "solving search..." << std::endl;
    start = st;
    goal = go;

    initialize();

    while (true) {
        computeShortestPath();
        break;
    }
    grid->getPath();
    std::cout << "completed search!\n" << std::endl;
}

void LPAStar::updateTile(Tile* tile) {
    if (tile != start) {
        tile->rhs = INT_MAX;
        // update the rhs value based on predecessors
        for (auto predecessor : tile->predecessors) {
            // tile->rhs = std::min(tile->rhs, predecessor->g + predecessor->calculateH(goal));
            tile->rhs = INT_MAX;
        }

        auto it = open.find(tile);
        // if priority queue is in open list, remove it
        if (it != open.end()) {
            open.erase(it);
        }
        // if tile is locally inconsistent, put that shit back
        if (tile->g != tile->rhs) {
            open.insert(tile);
        }
    }
}

void LPAStar::initialize() {
    start->updateRHS(0.);
    auto keyVal = start->calculateKeys(goal);
    start->updateKey(keyVal);
    open.insert(start);
}

void LPAStar::computeShortestPath() {

    auto q = *open.begin();
    while (q->key < goal->calculateKeys(goal) || goal->rhs != goal->g) {
        q = *open.begin();
        open.erase(open.begin());
        closed.insert(q->idx);

        if (q->g > q->rhs) {
            q->updateG(q->rhs);
        }
        else {
            q->updateG(INT_MAX);
            updateTile(q);
        }

        for (auto successor : grid->getSuccessors(q->idx)) {
            updateTile(successor);
        }
    }
}
