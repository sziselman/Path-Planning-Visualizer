#include "tile.h"


Tile::Tile() {}

Tile::Tile(int x, int y, sf::RectangleShape &shape) : x(x), y(y), shape(shape) {
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(outlineTileThickness);
}

Tile::~Tile() {}

void Tile::updateNeighbors(std::vector<int> neighbors) {
    neighbors = neighbors;
}

void Tile::setStartTile(void) {
    isStart = true;
    isGoal = false;
    isObstacle = false;
    isVisited = false;

    shape.setFillColor(startTileColor);
}

void Tile::setGoalTile(void) {
    isStart = false;
    isGoal = true;
    isObstacle = false;
    isVisited = false;

    shape.setFillColor(goalTileColor);
}

void Tile::setObstacleTile(void) {
    isStart = false;
    isGoal = false;
    isObstacle = true;

    shape.setFillColor(obstacleTileColor);
}

void Tile::setVisited(void) {
    isVisited = true;

    shape.setFillColor(visitedTileColor);
}
