#include "tile.h"


Tile::Tile(int x, int y, int idx, sf::RectangleShape shape) : x(x), y(y), idx(idx), shape(shape) {
}

void Tile::setDefaultTile(void) {
    // set default properties to tiles
    isStart = false;
    isGoal = false;
    isObstacle = false;

    shape.setFillColor(openTileColor);
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(tileOutlineThickness);
}

void Tile::setStartTile(void) {
    isStart = true;
    isGoal = false;
    isObstacle = false;

    shape.setFillColor(startTileColor);
}

void Tile::setGoalTile(void) {
    isStart = false;
    isGoal = true;
    isObstacle = false;

    shape.setFillColor(goalTileColor);
}

void Tile::setObstacleTile(void) {
    isStart = false;
    isGoal = false;
    isObstacle = true;

    shape.setFillColor(obstacleTileColor);
}
