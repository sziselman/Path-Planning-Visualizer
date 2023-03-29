/**
 * @brief Grid class used for organizing grid tiles for path planning visualizer
*/
#ifndef _GRID_H
#define _GRID_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <climits>
#include <iostream>
#include <set>

#include "tile.h"
#include "astar.h"
#include "lpastar.h"


class Grid {
    public:
        /// @brief Constructor for Grid class
        /// @param width Width of the SFML Rendered window
        /// @param height Height of the SFML Rendered window
        /// @param window SFML window object
        /// @param mouse SFML mouse object
        Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse);

        /// @brief Destructor for Grid class
        ~Grid();

        /// @brief Getter for the start tile
        /// @return Pointer to the start tile
        Tile* getStart();

        /// @brief Getter for the goal tile
        /// @return Pointer to the goal tile
        Tile* getGoal();

        /// @brief Displays start, goal, obstacle, and visited tiles
        void displayTiles();

        /// @brief Adds obstacles if user right clicks on an unoccupied tile on the grid
        void addObstacle();

        /// @brief Updates the start or goal tiles if the user left clicks the start or goal tires
        void updateStartGoalTiles();

        /// @brief Make Grid class a friend to AStar
        friend class AStar;

        /// @brief Make Grid class a friend to LPAStar
        friend class LPAStar;

    private:
        // window variables
        sf::RenderWindow& window;
        sf::Mouse& mouse;

        // tile variables
        static constexpr double tileDim = 40;
        int xTiles;
        int yTiles;

        // information about all available tiles
        int start;
        int goal;
        std::map<int, Tile*> tileMap;
        std::set<int> obstacles;

        // private helper functions
        /// @brief Makes a Tile object based on the index location on the grid
        /// @param idx The index of the tile on the grid
        /// @return A pointer to the Tile object created
        Tile* makeTileFromIdx(int idx);

        /// @brief Calculates the index location of where the mouse is located on the grid
        /// @return The index location on the grid
        int getTileIdxFromMousePos();

        /// @brief Calculates the index location from x, y coordinates
        /// @param pos A pair representin the x, y coordinates
        /// @return The index location on the grid
        int getTileIdxFromTilePos(std::pair<int, int> pos);

        /// @brief Checks if a pair of x, y coordinates is in bounds of the grid
        /// @param pos A pair representing the x, y coordinates
        /// @return True if in bounds, False if not in bounds
        bool isInBounds(std::pair<int, int> pos);

        /// @brief Sets a new location for the start or goal tiles
        /// @param isStart True if setting new location for the start tile, False if setting new location for goal tile
        void setNewTile(bool isStart);

        /// @brief Checks for all valid successors that are in bounds of the grid and not obstacles
        /// @param idx The index location of the tile to get successors to
        /// @return A vector containing pointers to the valid neighbors
        std::vector<Tile*> getSuccessors(int idx);

        /// @brief Traces back the path generated and updates the tile map to reflect path tiles
        void getPath();

};

#endif