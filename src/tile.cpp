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

double Tile::calculateG(const Tile* p) {
    return p->g + sqrt(pow(p->x - x, 2) + pow(p->y - y, 2));
}

double Tile::calculateH(const Tile* goal) {
    double dmax = std::max(abs(goal->x - x), abs(goal->y - y));
    double dmin = std::min(abs(goal->x - x), abs(goal->y - y));

    return cd * dmin + ca * (dmax - dmin);
}

std::pair<double, double> Tile::calculateKeys(const Tile* goal) {
    double k1 = std::min(g, rhs) + calculateH(goal);
    double k2 = std::min(g, rhs);
    return std::make_pair(k1, k2);
}

void Tile::updateParent(const Tile* p) {
    parent = p;
    g = calculateG(parent);
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
    return lhs->key < rhs->key;
}