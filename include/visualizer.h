/**
 * @brief Visualizer class for displaying the rendered window
*/

#include <SFML/Graphics.hpp>

#include "grid.h"


class Visualizer {
    public:
        Visualizer(int width, int height);
        ~Visualizer();

        void display(void);

    private:
        sf::RenderWindow window;
        sf::Mouse mouse;

        Grid grid;
};
