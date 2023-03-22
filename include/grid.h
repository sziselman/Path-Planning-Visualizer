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

        bool settingNewTile = false;

        // private helper functions
        Tile makeTileFromIdx(int idx);
        int getTileIdxFromMousePos(void);
        int getTileIdxFromTilePos(int x, int y);
        bool isInBounds(int x, int y);
        void setNewTile(bool isStart);

        // a* private functions
        std::map<int, Tile> getSuccessors(int idx, Tile &q);
};
