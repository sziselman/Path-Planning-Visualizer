/**
 * @brief Search class used as a base class for all preceding search algorithms
*/
#ifndef _SEARCH_H
#define _SEARCH_H

#include "tile.h"


class Search {
    public:
        Search() {}
        virtual ~Search() {}
        virtual void solve(Tile* st, Tile* go) = 0;
        virtual void examineChangedTiles() {};
    private:
};

#endif