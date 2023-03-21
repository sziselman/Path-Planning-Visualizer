#include <iostream>
#include <cmath>

#include "grid.h"

using namespace std;


Tile::Tile(int x, int y, int idx, sf::RectangleShape shape) : x(x), y(y), idx(idx), shape(shape) {
}

Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : width(width), height(height), 
                                                                                window(window), mouse(mouse) {
    xTiles = width / tileDim;
    yTiles = height / tileDim;

    int totalTiles = xTiles * yTiles;

    // add tiles to map
    for (int i = 0; i < totalTiles; i++) {
        sf::RectangleShape shape(sf::Vector2f(tileDim, tileDim));
        int x = i % xTiles;
        int y = i / xTiles;
        tileMap.push_back(Tile(x, y, i, shape));
    }

    // set properties of each tile in map
    for (int i = 0; i < totalTiles; i++) {
        double x_loc = double(tileMap[i].x * tileDim);
        double y_loc = double(tileMap[i].y * tileDim);

        tileMap[i].shape.setPosition(x_loc, y_loc);
        tileMap[i].shape.setFillColor(openTileColor);
        tileMap[i].shape.setOutlineColor(outlineTileColor);
        tileMap[i].shape.setOutlineThickness(tileOutlineThickness);
    }

    // set the start, goal positions
    tileMap.front().shape.setFillColor(startTileColor);
    tileMap.back().shape.setFillColor(goalTileColor);
}

Grid::~Grid() {}

void Grid::displayGrid(void) {
    for (auto tile : tileMap) {
        window.draw(tile.shape);
    }
}

void Grid::addObstacle(void) {
    auto pos = mouse.getPosition(window);

    int xTileLoc = ceil(pos.x / tileDim) -1;
    int yTileLoc = ceil(pos.y / tileDim) -1;

    int tile_idx = yTileLoc * xTiles + xTileLoc;

    tileMap[tile_idx].shape.setFillColor(obstacleTileColor);

    obstacleMap.push_back(tileMap[tile_idx]);
}

