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
#include <algorithm>
#include <set>

#include "tile.h"


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

        /// @brief Adds and updates obstacle position to make a "snake" that traverses the inner boundary of the grid
        void makeSnakeObstacle();

        /// @brief Checks for all valid successors that are in bounds of the grid and not obstacles
        /// @param tile The tile pointer to get successors from
        /// @return A vector containing pointers to the valid successors
        std::vector<Tile*> getSuccessors(const Tile* tile);

        std::set<Tile*> getChangedTiles();

        std::set<int> getObstacles();

    private:
        // window variables
        sf::RenderWindow& window;
        sf::Mouse& mouse;

        // tile variables
        static constexpr double tileDim = 100;
        int xTiles;
        int yTiles;

        // information about all available tiles
        int start;
        int goal;
        std::map<int, Tile*> tileMap;
        std::set<int> obstacles;
        std::set<int> changedIdxs;

        // snake variables
        std::vector<int> snakeTiles;
        int snakeTail = 0;
        int snakeLen;

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
};

#endif