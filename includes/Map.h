//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_MAP_H
#define IMS_MAP_H

#include <memory>
#include <vector>

#include "Cell.h"

class Cell;

class Map {
private:
    size_t width, height;
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;

public:
    Map(size_t w, size_t h);

    [[nodiscard]] std::unique_ptr<Cell>& at(size_t x, size_t y);

    [[nodiscard]] size_t getWidth() const { return width; }
    [[nodiscard]] size_t getHeight() const { return height; }

    void iterate();

    std::vector<Cell*> getCellsInRadius(int cellX, int cellY, int radius);
    Cell* findFloodDirectionNeighbor(int cellX, int cellY);
};

#endif //IMS_MAP_H
