/**
 * @brief Tile class used for representing and visualizing nodes in the search graph
*/
#include <SFML/Graphics.hpp>
#include <iostream>

struct Tile {
    public:
        int x;
        int y;
        int idx;
        sf::RectangleShape shape;

        bool isStart = false;
        bool isGoal = false;
        bool isObstacle = false;

        // visual properties of tiles
        static constexpr double tileOutlineThickness = 1;
        sf::Color openTileColor = sf::Color(255, 240, 245);
        sf::Color outlineTileColor = sf::Color::Black;
        sf::Color startTileColor = sf::Color::Red;
        sf::Color goalTileColor = sf::Color(216, 178, 209);
        sf::Color obstacleTileColor = sf::Color(100, 27, 48);

        Tile(int x, int y, int idx, sf::RectangleShape shape);

        void setDefaultTile(void);
        void setStartTile(void);
        void setGoalTile(void);
        void setObstacleTile(void);
};