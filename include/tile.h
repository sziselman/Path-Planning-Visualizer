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
        bool isVisited = false;

        // heuristic values
        double g;   // cost to get from start to current using path taken
        double h;   // estimated movement cost from current to goal
        double f;   // g + h

        std::vector<int> neighbors;

        // visual properties of tiles
        static constexpr double tileOutlineThickness = 1;
        sf::Color openTileColor = sf::Color(255, 240, 245);
        sf::Color visitedTileColor = sf::Color(255, 179, 71);
        sf::Color visitingTileColor = sf::Color(195, 205, 230);
        sf::Color outlineTileColor = sf::Color::Black;
        sf::Color startTileColor = sf::Color::Red;
        sf::Color goalTileColor = sf::Color(216, 178, 209);
        sf::Color obstacleTileColor = sf::Color(100, 27, 48);

        Tile(int x, int y, int idx, sf::RectangleShape shape);

        void updateNeighbors(std::vector<int> neighbors);
        void setDefaultTile(void);
        void setStartTile(void);
        void setGoalTile(void);
        void setObstacleTile(void);
};