//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_MAP_H
#define IMS_MAP_H

#include <memory>
#include <vector>

#include "Cell.h"
#include "IterationPhaseEnum.h"
#include "SpeciesRegistry.h"

class Cell;

class Map {
private:
    bool fertilization_;
    size_t iterationsSinceRain{};
    size_t iterationsSinceFertilisation{};
    size_t width;
    size_t height;
    std::vector<std::vector<std::unique_ptr<Cell>>> grid;

    bool expEvent(size_t averageRate, size_t iterationNumber);
    double getRainAmmount();

public:
    Map(size_t w, size_t h);

    [[nodiscard]] std::unique_ptr<Cell>& at(size_t x, size_t y);

    [[nodiscard]] size_t getWidth() const { return width; }
    [[nodiscard]] size_t getHeight() const { return height; }
    void setFertilization(bool fertilization);

    void iterate();
    //called after seeding map grid to connect cells
    void setUp();

    std::vector<Cell*> getCellsInRadius(int cellX, int cellY, int radius);
    Cell* findFloodDirectionNeighbor(int cellX, int cellY);
};

#endif //IMS_MAP_H
