#include "tile.h"


Tile::Tile() {}

Tile::Tile(int x, int y, int idx, sf::RectangleShape &shape) : x(x), y(y), idx(idx), shape(shape) {
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(outlineTileThickness);
}

Tile::~Tile() {}

void Tile::setStartTile(void) {
    g = 0.;
    f = 0.;

    shape.setFillColor(pathTileColor);
}

void Tile::setGoalTile(void) {
    shape.setFillColor(goalTileColor);
}

void Tile::setObstacleTile(void) {
    shape.setFillColor(obstacleTileColor);
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(outlineTileThickness);
}

void Tile::setVisited(void) {
    shape.setFillColor(visitedTileColor);
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(outlineTileThickness);
}

void Tile::setPath(void) {
    shape.setFillColor(pathTileColor);
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(outlineTileThickness);
}

void Tile::calculateF(const Tile* goal) {
    // calculate g
    g = parent->g + sqrt(pow(parent->x - x, 2) + pow(parent->y - y, 2));

    // calculate h
    // double h = abs(goal->x - x) + abs(goal->y - y);
    double dmax = std::max(abs(goal->x - x), abs(goal->y - y));
    double dmin = std::min(abs(goal->x - x), abs(goal->y - y));

    double h = cd * dmin + ca * (dmax - dmin);

    f = g + h;
}

bool TilePtrCompare::operator()(const Tile* lhs, const Tile* rhs) const {
    return lhs->f <= rhs->f;
}
