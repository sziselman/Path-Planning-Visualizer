#include "astar.h"


AStar::AStar(Grid* grid) : grid(grid) {}

void AStar::solve(Tile* st, Tile* go) {
    std::cout << "solving search..." << std::endl;
    start = st;
    goal = go;

    start->updateG(0.);
    start->updateF(0.);
    open.insert(start);

    double g, h, f;

    while (!open.empty()) {
        auto q = *open.begin();
        q->setClosed();
        closed.insert(q->idx);
        open.erase(open.begin());
        grid->displayTiles();

        if (q == goal) {
            break;
        }

        for (auto successor : grid->getSuccessors(q->idx)) {
            if (closed.find(successor->idx) != closed.end()) {
                continue;
            }

            g = calculateG(q, successor);
            h = calculateH(successor);
            f = g + h;

            auto it = open.find(successor);
            if (it != open.end()) {
                if (successor->f > f) {
                    open.erase(it);
                    successor->updateParent(q);
                    successor->updateG(g);
                    successor->updateF(f);
                    open.insert(successor);
                }
            }
            else {
                successor->updateParent(q);
                successor->updateG(g);
                successor->updateF(f);
                successor->setOpened();
                open.insert(successor);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    getPath();
    std::cout << "completed search!\n" << std::endl;
}

double AStar::calculateH(Tile* tile) {
    double dmax = std::max(abs(goal->x - tile->x), abs(goal->y - tile->y));
    double dmin = std::min(abs(goal->x - tile->x), abs(goal->y - tile->y));
    return cd * dmin + ca * (dmax - dmin);
}

double AStar::calculateG(Tile* from, Tile* to) {
    return from->g + sqrt(pow(from->x - to->x, 2) + pow(from->y - to->y, 2));
}

void AStar::getPath() {
    Tile* curr = goal;
    while (curr->parent != nullptr) {
        curr->setPath();
        curr = curr->parent;
    }
    curr->setPath();
}