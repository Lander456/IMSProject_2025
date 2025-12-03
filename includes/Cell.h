//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

#include "Soil.h"
#include "Terrain.h"
#include "Vegetation.h"
#include "Map.h"
#include "IterationPhaseEnum.h"

class Map;
class Vegetation;

class Cell {
public:
    int gridX_;
    int gridY_;
    Map& map_;
    Terrain terrain;
    Soil soil;
    std::unique_ptr<Vegetation> vegetation;
    double shade;
    //moisture first, nitre second
    std::pair<double,double> incomingSoilChanges;

    virtual void Iterate(IterationPhase phase);
    virtual void Fertilise();
    virtual void OnRain();
    virtual void SetUp();

    Cell(Map& map, int x, int y, TerrainTypesEnum terainType);
};

class HabitableCell : public Cell{
public:
    HabitableCell(Map& map, int x, int y, TerrainTypesEnum type);
    void SetUp() override;
    std::vector<Cell*> cellsInRange; //includes self
protected:
    Cell* floodDirectionCell_;

    void flood();
};

class DirtCell : public HabitableCell {
public:
    DirtCell(Map& map, int x, int y);
    void Iterate(IterationPhase phase) override;
    void OnRain() override;
};

class GravelCell : public HabitableCell {
public:
    GravelCell(Map& map, int x, int y);
    void Iterate(IterationPhase phase) override;
    void OnRain() override;
};

class FieldCell : public HabitableCell {
public:
    FieldCell(Map& map, int x, int y);
    void Iterate(IterationPhase phase) override;
    void OnRain() override;
    void Fertilise() override;
};

class WaterCell : public Cell {
protected:
    std::vector<Cell *> cellsInRange_;

public:
    WaterCell(Map& map, int x, int y);
    void Iterate(IterationPhase phase) override;
    void SetUp() override;
};

class RockCell : public Cell {
public:
    RockCell(Map& map, int x, int y);
};

#endif //IMS_CELL_H