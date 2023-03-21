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
    tileMap.front().isStart = true;

    tileMap.back().shape.setFillColor(goalTileColor);
    tileMap.back().isGoal = true;
}

Grid::~Grid() {}

void Grid::displayGrid(void) {
    for (auto tile : tileMap) {
        window.draw(tile.shape);
    }
}

int Grid::getTileIdxFromMousePos(void) {
    // determine position and index of tile
    auto pos = mouse.getPosition(window);

    int xTileLoc = ceil(pos.x / tileDim) -1;
    int yTileLoc = ceil(pos.y / tileDim) -1;

    return yTileLoc * xTiles + xTileLoc;
}

void Grid::addObstacle(void) {
    int tileIdx = getTileIdxFromMousePos();

    // check if tile is start or goal
    if (tileMap[tileIdx].isStart == true || tileMap[tileIdx].isGoal == true) {
        return;
    }
    else {
        tileMap[tileIdx].isObstacle = true;
        tileMap[tileIdx].shape.setFillColor(obstacleTileColor);
        obstacleMap.push_back(tileMap[tileIdx]);
    }
}

void Grid::updateSearch(void) {
    int tileIdx = getTileIdxFromMousePos();

    // check if tile is start, goal, obstacle or neither
    if (tileMap[tileIdx].isStart == true) {
        setStartTile();
    }
    else if (tileMap[tileIdx].isGoal == true) {
        setGoalTile();
    }
    else if (tileMap[tileIdx].isObstacle == true) {
        return;
    }
    else {
        startSearch();
    }
}

void Grid::setStartTile(void) {
    settingNewStart = true;

    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    while (settingNewStart == true) {
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            cout << "new start tile :D" << endl;
            settingNewStart = false;
        }
    }
}

void Grid::setGoalTile(void) {
    settingNewGoal = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(200));

    while (settingNewGoal == true) {
        if (mouse.isButtonPressed(sf::Mouse::Left)) {
            cout << "new goal tile :D" << endl;
            settingNewGoal = false;
        }
    }
}

void Grid::startSearch(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
