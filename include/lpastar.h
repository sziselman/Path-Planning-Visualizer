/**
 * @brief LPAStar class for searching and creating path using Lifelong Planning A* search algorithm
*/

#ifndef _LPA_STAR_H
#define _LPA_STAR_H

#include <climits>

#include "search.h"
#include "grid.h"
#include "tile.h"


class Grid;

class LPAStar : public Search {
    public:
        LPAStar(Grid* grid);
        void solve(Tile* st, Tile* go) override;
        void updateTile(Tile* tile);
    private:
        Grid* grid;

        Tile* start;
        Tile* goal;

        std::set<int> closed;
        std::set<Tile*, LPAStarTilePtrCompare> open;

        void initialize();

        void computeShortestPath();
};

#endif