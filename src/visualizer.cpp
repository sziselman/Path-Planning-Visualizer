#include <iostream>

#include "visualizer.h"


using namespace std;

Visualizer::Visualizer(int width, int height) : window(sf::VideoMode(width, height), "SFML works!"), 
                                                grid(width, height, window, mouse) {
    cout << "hey bitch" << endl;
}

Visualizer::~Visualizer() {}

void Visualizer::display(void) {
    sf::CircleShape shape(500.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) window.close();
            }

            window.clear();
            grid.displayGrid();
            window.display();

            if (mouse.isButtonPressed(sf::Mouse::Right)) {
                grid.addObstacle();
            }

            if (mouse.isButtonPressed(sf::Mouse::Left)) {
                grid.updateSearch();
            }
        }
}