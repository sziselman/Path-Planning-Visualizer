/**
 * @brief Grid class used for organizing grid blocks for path planning visualizer
*/

#include <SFML/Graphics.hpp>
#include <chrono>
#include <thread>
#include <cmath>
#include <iostream>


using namespace std;

struct Tile {
    public:
        int x;
        int y;
        int idx;
        sf::RectangleShape shape;

        bool isStart = false;
        bool isGoal = false;
        bool isObstacle = false;

        Tile(int x, int y, int idx, sf::RectangleShape shape);
};

class Grid {
    public:
        Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse);
        ~Grid();

        void displayGrid(void);
        void addObstacle(void);
        void updateSearch(void);

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
        std::vector<double> startPos;
        std::vector<double> goalPos;

        bool settingNewStart = false;
        bool settingNewGoal = false;

        // visual properties of tiles
        static constexpr double tileOutlineThickness = 1;
        sf::Color openTileColor = sf::Color(255, 240, 245);
        sf::Color outlineTileColor = sf::Color::Black;
        sf::Color startTileColor = sf::Color::Red;
        sf::Color goalTileColor = sf::Color(216, 178, 209);
        sf::Color obstacleTileColor = sf::Color(100, 27, 48);

        // private helper functions
        int getTileIdxFromMousePos(void);
        void setStartTile(void);
        void setGoalTile(void);
        void startSearch(void);
};
