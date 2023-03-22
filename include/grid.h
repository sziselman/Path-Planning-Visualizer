/**
 * @brief Grid class used for organizing grid blocks for path planning visualizer
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>
#include <unordered_set>

#include "tile.h"


class Grid {
    public:
        Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse);
        ~Grid();

        void displayDefaultGrid(void);
        void displayTiles(void);
        void addObstacle(void);
        void updateStartGoalTiles(void);

        void solveAStar(void);

    private:
        // window variables
        double width;
        double height;

        // tile variables
        static constexpr double tileDim = 40;
        int xTiles;
        int yTiles;
        int totalTiles;

        // visual properties
        static constexpr double outlineTileThickness = 1;
        sf::Color openTileColor = sf::Color(255, 240, 245);
        sf::Color outlineTileColor = sf::Color::Black;

        // window, mouse object from the visualizer
        sf::RenderWindow& window;
        sf::Mouse& mouse;

        // information about all available tiles
        std::vector<Tile> tileMap;

        std::pair<int, Tile> start;
        std::pair<int, Tile> goal;
        std::map<int, Tile> obstacles;

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
