#include "tile.h"


Tile::Tile() {}

Tile::Tile(int x, int y, sf::RectangleShape &shape) : x(x), y(y), shape(shape) {
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(outlineTileThickness);
}

Tile::~Tile() {}

bool Tile::operator<(Tile &rhs) {
    return f < rhs.f;
}

// void Tile::getSuccessors(void) {
//     neighbors = neighbors;
// }

void Tile::setStartTile(void) {
    // update booleans
    isStart = true;
    isGoal = false;
    isObstacle = false;
    isVisited = false;

    // update heuristics
    g = 0.;
    h = 0.;
    f = 0.;

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

void Tile::addParent(const int idx, Tile &tile) {
    parents.insert({idx, tile});
}

void Tile::calculateG(const Tile &tile) {
    double dist = sqrt(pow(tile.x - x, 2) + pow(tile.y - y, 2));
    g = tile.g + dist;
}

void Tile::calculateH(const Tile &tile) {
    /**
     * @brief calculates the non-uniform diagonal distance, assuming we are allowed to move in all 8 directions
    */
    double dmax = std::max(abs(x - tile.x), abs(y - tile.y));
    double dmin = std::min(abs(x - tile.x), abs(y - tile.y));

    h = cd * dmin + ca * (dmax - dmin);
}

void Tile::calculateF(void) {
    f = g + h;
    std::cout << "f value: " << f << std::endl;
}