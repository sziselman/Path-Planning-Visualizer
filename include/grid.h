/**
 * @brief Grid class used for organizing grid blocks for path planning visualizer
*/

#include <SFML/Graphics.hpp>


using namespace std;

class Tile {
    public:
        int x;
        int y;
        int idx;
        sf::RectangleShape shape;
        
        Tile(int x, int y, int idx, sf::RectangleShape shape);

        private:
};

class Grid {
    public:
        Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse);
        ~Grid();

        void displayGrid(void);
        void addObstacle(void);

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

        // visual properties of tiles
        static constexpr double tileOutlineThickness = 1;
        sf::Color openTileColor = sf::Color(255, 240, 245);
        sf::Color outlineTileColor = sf::Color::Black;
        sf::Color startTileColor = sf::Color::Red;
        sf::Color goalTileColor = sf::Color(216, 178, 209);
        sf::Color obstacleTileColor = sf::Color(100, 27, 48);
};
