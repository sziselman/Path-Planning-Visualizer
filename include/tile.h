/**
 * @brief Tile class used for representing and visualizing nodes in the search graph
*/
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
        double f;                               // g + h
        static constexpr double ca = 1.;        // cost of adjacent movement
        static constexpr double cd = 1.41421;   // cost of diagonal movements

        const Tile* parent = nullptr;

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
        
        /// @brief Calculates the g-value used to determine the distance traveled
        double calculateG(const Tile* parent);

        /// @brief Calculates the f-value used to determine the "shortest" path to the goal
        double calculateH(const Tile* goal);
};

struct TilePtrCompare {
    /// @brief Overload on comparison operator, used to sort a set of Tile pointers
    /// @param lhs Pointer to the left-hand side Tile
    /// @param rhs Pointer to the right-hand side Tile
    /// @return True if the left-hand side Tile's f-value is less than the right-hand side Tile's f-vale, False otherwise
    bool operator()(const Tile* lhs, const Tile* rhs) const;
};
