/**
 * @brief AStar class for searching and creating path using A* search algorithm
*/

#ifndef _A_STAR_H
#define _A_STAR_H

#include "tile.h"
#include "grid.h"
#include "search.h"


// class Grid;

class AStar : public Search {
    public:  
        /// @brief Constructor for AStar class
        /// @param grid Pointer to the grid that stores tile information
        AStar(Grid& grid);

        /// @brief Destructor for AStar class
        ~AStar();

        /// @brief Searches for an optimal path from start to goal
        /// @param st Pointer to start tile
        /// @param go Pointer to goal tile
        void solve(Tile* st, Tile* go) override;

    private:
        // Grid* grid;
        Grid grid;

        Tile* start;
        Tile* goal;

        std::set<int> closed;
        std::set<Tile*, AStarTilePtrCompare> open;

        static constexpr double ca = 1.;        // cost of adjacent movement
        static constexpr double cd = 1.41421;   // cost of diagonal movements

        /// @brief Calculates the estimated cost to move from current to goal using diagonal distance
        /// @param tile Pointer to the current tile
        /// @return The diagonal distance from current to goal
        double calculateH(Tile* tile);

        /// @brief Calculates the cost to travel along the traversed path
        /// @param from Pointer to the predecessor tile
        /// @param to Pointer to the current tile
        /// @return The distance traveled from predecessor tile to current tile
        double calculateG(Tile* from, Tile* to);

        void getPath();
};

#endif