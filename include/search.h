/**
 * @brief Search class used as a base class for all preceding search algorithms
*/
#ifndef _SEARCH_H
#define _SEARCH_H

#include "tile.h"


class Search {
    public:
        virtual void solve(Tile* st, Tile* go) {}
    private:
};

#endif