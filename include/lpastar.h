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

        /// @brief Calculates the estimated cost to move from current to goal using diagonal distance
        /// @param tile Pointer to the current tile
        /// @return The diagonal distance from current to goal
        double calculateH(Tile* tile);

        /// @brief Calculates the cost to travel along the traversed path
        /// @param from Pointer to the predecessor tile
        /// @param to Pointer to the current tile
        /// @return The distance traveled from predecessor tile to current tile
        double calculateG(Tile* from, Tile* to);

        std::pair<double, double> calculateKey(Tile* tile);
};

#endif