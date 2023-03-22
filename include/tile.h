/**
 * @brief Tile class used for representing and visualizing nodes in the search graph
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cfloat>
#include <cmath>


struct Tile {
    public:
        int x;
        int y;
        sf::RectangleShape shape;

        bool isStart = false;
        bool isGoal = false;
        bool isObstacle = false;
        bool isVisited = false;

        // heuristic values
        double g;   // cost to get from start to current using path taken
        double h;   // estimated movement cost from current to goal
        double f;   // g + h
        static constexpr double ca = 1.;        // cost of adjacent movement
        static constexpr double cd = 1.41421;   // cost of diagonal movements

        // std::vector<int> neighbors;
        std::map<int, Tile> successors;
        std::map<int, Tile> parents;

        // visual properties of tiles
        static constexpr double outlineTileThickness = 1;
        sf::Color visitedTileColor = sf::Color(255, 179, 71);
        sf::Color visitingTileColor = sf::Color(195, 205, 230);
        sf::Color outlineTileColor = sf::Color::Black;
        sf::Color startTileColor = sf::Color::Red;
        sf::Color goalTileColor = sf::Color(216, 178, 209);
        sf::Color obstacleTileColor = sf::Color(100, 27, 48);

        Tile();
        Tile(int x, int y, sf::RectangleShape &shape);
        ~Tile();
        bool operator<(const Tile &rhs) const;
        
        void setStartTile(void);
        void setGoalTile(void);
        void setObstacleTile(void);
        void setVisited(void);

        void addParent(const int idx, Tile &tile);

        void calculateG(const Tile &tile);
        void calculateH(const Tile &tile);
        void calculateF(void);
};