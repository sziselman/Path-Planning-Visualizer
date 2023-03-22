#include "a_star.h"


AStar::AStar(int startTileIdx, int goalTileIdx, std::vector<Tile> tileMap) :  startTileIdx(startTileIdx),
                                                                              goalTileIdx(goalTileIdx),
                                                                              tileMap(tileMap) {
    std::cout << "initializing a* algorithm" << std::endl;
}