#include "tile.h"


Tile::Tile() {}

Tile::Tile(int x, int y, int idx, sf::RectangleShape &shape) : x(x), y(y), idx(idx), shape(shape) {
    shape.setOutlineColor(outlineTileColor);
    shape.setOutlineThickness(outlineTileThickness);
}

Tile::~Tile() {}

void Tile::setStartTile(void) {
    g = 0.;
    h = 0.;
    f = 0.;

    shape.setFillColor(pathTileColor);
}

void Tile::setGoalTile(void) {
    shape.setFillColor(goalTileColor);
}

void Tile::setObstacleTile(void) {
    shape.setFillColor(obstacleTileColor);
}

void Tile::setVisited(void) {
    shape.setFillColor(visitedTileColor);
}

void Tile::setPath(void) {
    shape.setFillColor(pathTileColor);
}

void Tile::calculateG(void) {
    double dist = sqrt(pow(parent->x - x, 2) + pow(parent->y - y, 2));
    g = parent->g + dist;
}

void Tile::calculateH(const Tile* tile) {
    double dmax = std::max(abs(x - tile->x), abs(y - tile->y));
    double dmin = std::min(abs(x - tile->x), abs(y - tile->y));

    h = cd * dmin + ca * (dmax - dmin);
}

void Tile::calculateF(void) {
    f = g + h;
}

bool TilePtrCompare::operator()(const Tile* lhs, const Tile* rhs) const {
    // if tiles have the same f value, sort by index
    if (lhs->f == rhs->f) {
        return lhs->idx < rhs->idx;
    }
    else {
        return lhs->f < rhs->f;
    }
}
