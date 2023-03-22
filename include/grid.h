/**
 * @brief Grid class used for organizing grid blocks for path planning visualizer
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>

#include "tile.h"


class Grid {
    public:
        Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse);
        ~Grid();

        void displayGrid(void);
        void addObstacle(void);
        void updateGrid(void);

    private:
        // window variables
        double width;
        double height;

        // tile variables
        static constexpr double tileDim = 40;
        int xTiles;
        int yTiles;
        int totalTiles;

        // window, mouse object from the visualizer
        sf::RenderWindow& window;
        sf::Mouse& mouse;

        // information about all available tiles
        std::vector<Tile> tileMap;
        std::vector<Tile> obstacleMap;
        int startTileIdx;
        int goalTileIdx;

        bool settingNewStart = false;
        bool settingNewGoal = false;

        // private helper functions
        int getTileIdxFromMousePos(void);
        int getTileIdxFromTilePos(int x, int y);
        std::vector<std::pair<int, int>> getNeighborIdxsFromTilePos(int x, int y);
        std::vector<int> getNeighborsFromTilePos(int x, int y);
        bool isOutOfBounds(int x, int y);
        void setStartTile(void);
        void setGoalTile(void);
        void startSearch(void);
};
