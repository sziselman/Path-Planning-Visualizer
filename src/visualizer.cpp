#include <iostream>

#include "visualizer.h"


using namespace std;

Visualizer::Visualizer(int width, int height) : window(sf::VideoMode(width, height), "Path Planning Visualizer"), 
                                                grid(width, height, window, mouse) {}

Visualizer::~Visualizer() {}

void Visualizer::render(void) {
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

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                searchType = "astar";
                algo = new AStar(&grid);
                solveSearch = true;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) {
                searchType = "lpastar";
                algo = new LPAStar(&grid);
                solveSearch = true;
            }
    }
    else {
        if (searchType == "astar") {
            algo->solve(grid.getStart(), grid.getGoal());
            solveSearch = false;
        }
        else if (searchType == "lpastar") {
            algo->solve(grid.getStart(), grid.getGoal());
            // grid.makeSnakeObstacle();
            // algo->examineChangedTiles();
            solveSearch = false;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(120));
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