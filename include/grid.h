/**
 * @brief Grid class used for organizing grid blocks for path planning visualizer
*/

#include <SFML/Graphics.hpp>


using namespace std;

class Grid {
    public:
        Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse);
        ~Grid();

        void displayGrid(void);
        void addObstacle(void);

    private:
        int width;
        int height;

        static constexpr double tileDim = 40;
        int widthTiles;
        int heightTiles;

        sf::RenderWindow& window;
        sf::Mouse& mouse;

        std::vector<sf::RectangleShape> tileMap;
        std::vector<double> startPos;
        std::vector<double> goalPos;

        std::vector<sf::RectangleShape> obstacleMap;

        static constexpr double tileOutlineThickness = 1;

        sf::Color openTileColor = sf::Color(255, 240, 245);
        sf::Color outlineTileColor = sf::Color::Black;
        sf::Color startTileColor = sf::Color::Red;
        sf::Color goalTileColor = sf::Color(216, 178, 209);
        sf::Color obstacleTileColor = sf::Color(100, 27, 48);

        void makeGrid(void);
};
