#include <iostream>

#include "visualizer.h"


using namespace std;

Visualizer::Visualizer(int width, int height) : window(sf::VideoMode(width, height), "SFML works!"), 
                                                grid(width, height, window, mouse) {
    cout << "initializing path planning visualizer" << endl;

    // algorithm()
}

Visualizer::~Visualizer() {}

void Visualizer::display(void) {

    while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear();
            grid.displayDefaultGrid();
            grid.displayTiles();
            window.display();

            if (mouse.isButtonPressed(sf::Mouse::Right)) {
                grid.addObstacle();
            }

            if (mouse.isButtonPressed(sf::Mouse::Left)) {
                grid.updateStartGoalTiles();
            }

            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
            //     cout << "starting serach" << endl;
            // }

        }
}