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

        static constexpr double ca = 1.;        // cost of adjacent movement
        static constexpr double cd = 1.41421;   // cost of diagonal movements

        void initialize();

        void computeShortestPath();

        double calculateH(Tile* tile);

        std::pair<double, double> calculateKey(Tile* tile);
};

#endif