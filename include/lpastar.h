/**
 * @brief LPAStar class for searching and creating path using Lifelong Planning A* search algorithm
*/

#ifndef _LPA_STAR_H
#define _LPA_STAR_H

#include "search.h"
#include "grid.h"


class LPAStar : public Search {
    public:
        LPAStar(Grid &grid);
        void solve(Tile* st, Tile* go) override;

    private:
};

#endif