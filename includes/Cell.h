//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

#include "Soil.h"
#include "Terrain.h"
#include "Vegetation.h"
#include "Map.h"

class Map;

class Cell {
protected:
    Map& map_;
    int gridX_;
    int gridY_;

public:
    Terrain terrain;
    Soil soil;
    Vegetation vegetation;
    double shade;

    virtual void Iterate();
    virtual void Fertilise();
    virtual void OnRain();

    Cell(Map& map, int x, int y, TerrainTypesEnum terainType);
};

class HabitableCell : public Cell{
public:
        HabitableCell(Map& map, int x, int y, TerrainTypesEnum type);

protected:
    Cell* floodDirectionCell_;

    void findFloodDirectionCell();

    void floodNitre();
};

class DirtCell : public HabitableCell {
public:
    DirtCell(Map& map, int x, int y);
    void Iterate() override;
    void OnRain() override;
};

class GravelCell : public HabitableCell {
public:
    GravelCell(Map& map, int x, int y);
    void Iterate() override;
    void OnRain() override;
};

class FieldCell : public HabitableCell {
public:
    FieldCell(Map& map, int x, int y);
    void Iterate() override;
    void OnRain() override;
    void Fertilise() override;
};

class WaterCell : public Cell {
protected:
    std::vector<Cell*> cellsInRange_;

public:
    WaterCell(Map& map, int x, int y);
    void Iterate() override;
};

class RockCell : public Cell {
public:
    RockCell(Map& map, int x, int y);
};

#endif //IMS_CELL_H