/**
 * @brief AStar class for searching and creating path using A* search algorithm
*/

#ifndef _A_STAR_H
#define _A_STAR_H

#include "grid.h"
#include "tile.h"
#include "search.h"


class Grid;

class AStar : public Search {
    public:
        /// @brief Constructor for AStar class
        /// @param grid Pointer to the grid that stores tile information
        AStar(Grid* grid);

        /// @brief Searches for an optimal path from start to goal
        /// @param st Pointer to start tile
        /// @param go Pointer to goal tile
        void solve(Tile* st, Tile* go) override;

    private:
        Grid* grid;

        Tile* start;
        Tile* goal;

        std::set<int> closed;
        std::set<Tile*, AStarTilePtrCompare> open;
};

#endif