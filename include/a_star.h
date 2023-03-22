/**
 * @brief AStar class for implementing A* algorithm on a grid
*/
#include <iostream>

#include "grid.h"


class AStar {
    public:
        AStar(int startTileIdx, int goalTileIdx, std::vector<Tile> tileMap);


    private:
        int startTileIdx;
        int goalTileIdx;
        std::vector<Tile> tileMap;

        std::unordered_set<int> openList;
        std::map<int, bool> closedList;
};
