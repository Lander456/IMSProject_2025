//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_MAP_H
#define IMS_MAP_H

#include <memory>
#include <vector>

#include "Cell.h"


class Map {
private:
    size_t width, height;
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;

public:
    Map(const size_t w, const size_t h) : width(w), height(h) {
        grid.resize(h);
        for (auto& row : grid) {
            row.resize(width);
        }
    }

    Cell& at(size_t x, size_t y);

    [[nodiscard]] size_t getWidth() const { return width; }
    [[nodiscard]] size_t getHeight() const { return height; }

    void iterate(int numberOfIterations);
};

#endif //IMS_MAP_H
