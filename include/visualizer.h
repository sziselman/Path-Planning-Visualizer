/**
 * @brief Visualizer class for displaying the rendered window
*/
#ifndef _VISUALIZER_H
#define _VISUALIZER_H

#include <SFML/Graphics.hpp>
#include <string.h>

#include "grid.h"
#include "astar.h"


class Visualizer {
    public:
        /// @brief Constructor for Visualizer class
        /// @param width The width of the window
        /// @param height The height of the window
        Visualizer(int width, int height);

        /// @brief Destructor for Visualizer class
        ~Visualizer();

        /// @brief Render all drawings to the window
        void render();

        /// @brief Updates the state of the visualizer
        void update();

        /// @brief Triggers an event to quit if the user closes the window
        /// @return True if the user closes the window, False if not
        bool quit();

    private:
        sf::RenderWindow window;
        sf::Mouse mouse;
        Grid grid;
        bool solveSearch = false;
        std::string searchType;
};

#endif