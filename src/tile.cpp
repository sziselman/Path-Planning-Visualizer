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
    shape.setFillColor(defaultColor);
}

void Tile::setStart() {
    g = 0.;
    f = 0.;
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

double Tile::calculateG(const Tile* parent) {
    return parent->g + sqrt(pow(parent->x - x, 2) + pow(parent->y - y, 2));
}

double Tile::calculateH(const Tile* goal) {
    double dmax = std::max(abs(goal->x - x), abs(goal->y - y));
    double dmin = std::min(abs(goal->x - x), abs(goal->y - y));

    return cd * dmin + ca * (dmax - dmin);
}

bool TilePtrCompare::operator()(const Tile* lhs, const Tile* rhs) const {
    if (lhs->f == rhs->f) {
        return lhs->g < rhs->g;
    }
    else {
        return lhs->f < rhs->f;
    }
}
