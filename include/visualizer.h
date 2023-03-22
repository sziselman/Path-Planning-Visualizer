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
        bool setDefaultDisplay = false;
        sf::RenderWindow window;
        sf::Mouse mouse;

        Grid grid;
};
