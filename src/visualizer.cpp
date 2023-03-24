#include <iostream>

#include "visualizer.h"


using namespace std;

Visualizer::Visualizer(int width, int height) : window(sf::VideoMode(width, height), "Path Planning Visualizer"), 
                                                grid(width, height, window, mouse) {}

Visualizer::~Visualizer() {}

void Visualizer::render(void) {
    grid.displayDefaultGrid();
    grid.displayTiles();
    window.display();
}

void Visualizer::update(void) {
    if (!solveSearch) {
        if (mouse.isButtonPressed(sf::Mouse::Right)) {
                grid.addObstacle();
            }

            if (mouse.isButtonPressed(sf::Mouse::Left)) {
                grid.updateStartGoalTiles();
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                solveSearch = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                
            }
    }
    else {
        grid.solveAStar();
        solveSearch = false;
    }

    window.clear();
}

bool Visualizer::quit(void) {
    sf::Event event;
    while(window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            return true;
        }
    }
    return false;
}