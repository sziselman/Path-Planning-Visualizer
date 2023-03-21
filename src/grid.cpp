#include <iostream>
#include <cmath>

#include "grid.h"

using namespace std;

Grid::Grid(int width, int height, sf::RenderWindow& window, sf::Mouse& mouse) : width(width), height(height), 
                                                                                window(window), mouse(mouse) {
    makeGrid();
}

Grid::~Grid() {}

void Grid::displayGrid(void) {
    for (auto tile : tileMap) {
        window.draw(tile);
    }
}

void Grid::addObstacle(void) {
    auto pos = mouse.getPosition(window);

    int xTileLoc = ceil(pos.x / tileDim) -1;
    int yTileLoc = ceil(pos.y / tileDim) -1;

    int tile_idx = yTileLoc * widthTiles + xTileLoc;

    tileMap[tile_idx].setFillColor(obstacleTileColor);

    obstacleMap.push_back(tileMap[tile_idx]);
}

void Grid::makeGrid(void) {
    widthTiles = width / tileDim;
    heightTiles = height / tileDim;
    int totalTiles = widthTiles * heightTiles;
    cout << "there are " << totalTiles << " total tiles" << endl;

    // add tiles to map
    for (int i = 0; i < totalTiles; i++) {
        tileMap.push_back(sf::RectangleShape(sf::Vector2f(tileDim, tileDim)));
    }

    // set properties of each tile in map
    for (int i = 0; i < totalTiles; i++) {
        double x_loc = double(i % widthTiles) * tileDim;
        double y_loc = double(i / widthTiles) * tileDim;

        tileMap[i].setPosition(x_loc, y_loc);
        tileMap[i].setFillColor(openTileColor);
        tileMap[i].setOutlineColor(outlineTileColor);
        tileMap[i].setOutlineThickness(tileOutlineThickness);
    }

    // set the start, goal positions
    tileMap.front().setFillColor(startTileColor);
    tileMap.back().setFillColor(goalTileColor);
    
}
