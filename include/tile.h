/**
 * @brief Tile class used for representing and visualizing nodes in the search graph
*/
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cfloat>
#include <cmath>
#include <set>


struct Tile {
    public:
        int x;
        int y;
        int idx;
        sf::RectangleShape shape;

        double g;
        double f;                               // g + h
        static constexpr double ca = 1.;        // cost of adjacent movement
        static constexpr double cd = 1.41421;   // cost of diagonal movements

        const Tile* parent = nullptr;

        // visual properties of tiles
        static constexpr double outlineTileThickness = 1;
        sf::Color visitedTileColor = sf::Color(195, 205, 230);
        sf::Color outlineTileColor = sf::Color::Black;
        sf::Color pathTileColor = sf::Color(220, 20, 60);
        sf::Color goalTileColor = sf::Color(216, 178, 209);
        sf::Color obstacleTileColor = sf::Color(100, 27, 48);

        /// @brief Empty constructor for Tile class
        Tile();

        /// @brief Constructor for Tile class
        /// @param x X coordinate of the tile
        /// @param y Y coordinate of the tile
        /// @param idx Index location of the tile
        /// @param shape SFML Shape used to visualize the tile
        Tile(int x, int y, int idx, sf::RectangleShape &shape);

        /// @brief Destructor for Tile class
        ~Tile();
        
        /// @brief Changes the tile to the start color
        void setStartTile();

        /// @brief Changes the tile to the goal color
        void setGoalTile();

        /// @brief Changes the tile to the obstacle color
        void setObstacleTile();

        /// @brief Changes the tile to the visited color
        void setVisited();

        /// @brief Changes the tile to the traversed path color
        void setPath();

        // /// @brief Calculates the distance traversed along the created trajectory using the most recent parent
        // // void calculateG();
        // void calculateG(const Tile* tile);

        // /// @brief Calculates the non-uniform diagonal distance as a heuristic (assuming moving in 8 directions)
        // /// @param tile A pointer to the Tile object representing the goal
        // void calculateH(const Tile* tile);

        /// @brief Calculates the f-value used to determine the "shortest" path to the goal
        void calculateF(const Tile* goal);
};

struct TilePtrCompare {
    /// @brief Overload on comparison operator, used to sort a set of Tile pointers
    /// @param lhs Pointer to the left-hand side Tile
    /// @param rhs Pointer to the right-hand side Tile
    /// @return True if the left-hand side Tile's f-value is less than the right-hand side Tile's f-vale, False otherwise
    bool operator()(const Tile* lhs, const Tile* rhs) const;
};
