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

            g = successor->calculateG(q);
            h = calculateH(successor);
            f = g + h;

            auto it = open.find(successor);
            if (it != open.end()) {
                if (successor->f > f) {
                    open.erase(it);
                    successor->updateParent(q);
                    successor->updateF(f);
                    open.insert(successor);
                }
            }
            else {
                successor->updateParent(q);
                successor->updateF(f);
                successor->setOpened();
                open.insert(successor);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    grid->getPath();
    std::cout << "completed search!\n" << std::endl;
}

double AStar::calculateH(Tile* tile) {
    double dmax = std::max(abs(goal->x - tile->x), abs(goal->y - tile->y));
    double dmin = std::min(abs(goal->x - tile->x), abs(goal->y - tile->y));
    return cd * dmin + ca * (dmax - dmin);
}
