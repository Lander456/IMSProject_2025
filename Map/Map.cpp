//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Map.h"

Cell & Map::at(const size_t x, const size_t y) {
    return this->grid[x][y];
}