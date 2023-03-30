/**
 * @brief Tile class used for representing and visualizing nodes in the search graph
*/
#ifndef _TILE_H
#define _TILE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <cfloat>
#include <climits>
#include <cmath>
#include <set>


struct Tile {
    public:
        int x;
        int y;
        int idx;
        sf::RectangleShape shape;

        double g;
        double f;
        double rhs;
        std::pair<double, double> key;

        Tile* parent = nullptr;

        // sets for LPA*
        std::set<Tile*> predecessors;

        // visual properties of tiles
        sf::Color defaultColor = sf::Color(251, 174, 210);
        sf::Color openedColor = sf::Color(246, 120, 40);
        sf::Color closedColor = sf::Color(195, 205, 230);
        sf::Color pathColor = sf::Color(220, 20, 60);
        sf::Color goalColor = sf::Color(216, 178, 209);
        sf::Color obstacleColor = sf::Color(100, 27, 48);

        /// @brief Empty constructor for Tile class
        Tile();

        /// @brief Constructor for Tile class
        /// @param x X coordinate of the tile
        /// @param y Y coordinate of the tile
        /// @param idx Index location of the tile
        /// @param dim dimension of the square tile
        Tile(int x, int y, int idx, double dim);

        /// @brief Destructor for Tile class
        ~Tile();
        
        /// @brief Changes the tile to the start color
        void setDefault();

        /// @brief Changes the tile to the start color
        void setStart();

        /// @brief Changes the tile to the goal color
        void setGoal();

        /// @brief Changes the tile to the obstacle color
        void setObstacle();

        /// @brief Changes the tile to the open color
        void setOpened();

        /// @brief Changes the tile to the visited color
        void setClosed();

        /// @brief Changes the tile to the traversed path color
        void setPath();

        /// @brief Updates the parent pointer and recalculates g
        /// @param p The pointer to the parent tile
        void updateParent(Tile* p);

        /// @brief Updates the current f-value
        /// @param val The new f-value
        void updateF(double val);

        /// @brief Updates the current g-value
        /// @param val The new g-value
        void updateG(double val);

        /// @brief Updates the current rhs value
        /// @param val The new rhs value
        void updateRHS(double val);

        /// @brief Updates the key value used to sort the priority queue
        /// @param keyVal The pair of key values, k1 and k2
        void updateKey(std::pair<double, double> keyVal);
};

struct AStarTilePtrCompare {
    /// @brief Overload on comparison operator, used to sort a set of Tile pointers
    /// @param lhs Pointer to the left-hand side Tile
    /// @param rhs Pointer to the right-hand side Tile
    /// @return True if the left-hand side Tile's f-value is less than the right-hand side Tile's f-vale, False otherwise
    bool operator()(const Tile* lhs, const Tile* rhs) const;
};

struct LPAStarTilePtrCompare {
    /// @brief Overload on comparison operator, used to sort priority queue by k1 first, then k2
    /// @param lhs Pointer to the left-hand side Tile
    /// @param rhs Pointer to the right-hand side tile
    /// @return True if left-hand side Tile's k1 value is less than the right-hand side Tile's k1 value. If equal, looks to k2
    bool operator() (const Tile* lhs, const Tile* rhs) const;
};

#endif