#include "tile.h"


Tile::Tile() {}

Tile::Tile(int x, int y, int idx, double dim) : x(x), y(y), idx(idx), shape(sf::Vector2f(dim, dim)) {
    shape.setPosition(x * dim, y * dim);
    shape.setOutlineColor(sf::Color::Black);
    shape.setOutlineThickness(1);
}

Tile::~Tile() {}

void Tile::setDefault() {
    g = INT_MAX;
    f = INT_MAX;
    rhs = INT_MAX;
    shape.setFillColor(defaultColor);
}

void Tile::setStart() {
    shape.setFillColor(pathColor);
}

void Tile::setGoal() {
    shape.setFillColor(closedColor);
}

void Tile::setObstacle() {
    shape.setFillColor(obstacleColor);
}

void Tile::setClosed() {
    shape.setFillColor(closedColor);
}

void Tile::setOpened() {
    shape.setFillColor(openedColor);
}

void Tile::setPath() {
    shape.setFillColor(pathColor);
}

void Tile::updateParent(Tile* p) {
    parent = p;
}

void Tile::updateF(double val) {
    f = val;
}

void Tile::updateG(double val) {
    g = val;
}

void Tile::updateRHS(double val) {
    rhs = val;
}

void Tile::updateKey(std::pair<double, double> keyVal) {
    key = keyVal;
}

bool AStarTilePtrCompare::operator()(const Tile* lhs, const Tile* rhs) const {
    if (lhs->f == rhs->f) {
        return lhs->g < rhs->g;
    }
    else {
        return lhs->f < rhs->f;
    }
}

bool LPAStarTilePtrCompare::operator()(const Tile* lhs, const Tile* rhs) const {
    return lhs->key <= rhs->key;
}