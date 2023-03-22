/**
 * @brief Visualizer class for displaying the rendered window
*/

#include <SFML/Graphics.hpp>

#include "grid.h"


class Visualizer {
    public:
        Visualizer(int width, int height);
        ~Visualizer();

        // void display(void);
        void render(void);
        void update(void);
        bool quit(void);

    private:
        bool solveSearch = false;
        bool setDefaultDisplay = false;
        sf::RenderWindow window;
        sf::Mouse mouse;

        Grid grid;
};
