/**
 * @brief Grid class used for organizing grid blocks for path planning visualizer
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
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

        /// @brief Displays a default grid for tiles not visited
        void displayDefaultGrid();

        /// @brief Displays start, goal, obstacle, and visited tiles
        void displayTiles();

        /// @brief Adds obstacles if user right clicks on an unoccupied tile on the grid
        void addObstacle();

        /// @brief Updates the start or goal tiles if the user left clicks the start or goal tires
        void updateStartGoalTiles();

        /// @brief Generates a path to get from start to goal using A* Search Algorithm
        void solveAStar();

    private:
        // window variables
        double width;
        double height;
        sf::RenderWindow& window;
        sf::Mouse& mouse;

        // tile variables
        static constexpr double tileDim = 40;
        int xTiles;
        int yTiles;
        int totalTiles;

        // visual properties
        static constexpr double outlineTileThickness = 1;
        sf::Color openTileColor = sf::Color(255, 240, 245);
        sf::Color outlineTileColor = sf::Color::Black;

        // information about all available tiles
        std::pair<int, Tile*> start;
        std::pair<int, Tile*> goal;
        std::map<int, Tile*> tileMap;
        std::set<int> closed;
        std::vector<int> path;
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
        /// @param x The x coordinate (increasing left to right)
        /// @param y The y coordinate (increasing top to bottom)
        /// @return The index location on the grid
        int getTileIdxFromTilePos(int x, int y);

        /// @brief Checks if a pair of x, y coordinates is in bounds of the grid
        /// @param pos A pair representing the x, y coordinates
        /// @return True if in bounds, False if not in bounds
        bool isInBounds(std::pair<int, int> pos);

        /// @brief Sets a new location for the start or goal tiles
        /// @param isStart True if setting new location for the start tile, False if setting new location for goal tile
        void setNewTile(bool isStart);

        /// @brief Draws all the tiles that have been visited to the window
        void displayVisitedTiles();

        /// @brief Draws all the path tiles that are respective to the current visited tile
        void displayPathTiles();

        /// @brief Checks for all valid successors that are in bounds of the grid and not obstacles
        /// @param idx The index location of the tile to get successors to
        /// @return A vector containing index locations of all the valid successors
        // std::vector<int> getSuccessors(int idx);
        std::vector<Tile*> getSuccessors(const Tile* tile);

        /// @brief Updates the traversed path by tracing the parents until at the start tile
        /// @param idx The index location of the tile to get the path to
        void getTraversedPath(int idx);
};
