//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Cell.h"

class RockCell : public Cell {
public:
    RockCell(Map& map) : Cell(map, TerrainTypesEnum::Rock)
    {

    }

};


class DirtCell : public Cell {
public:
    DirtCell(Map& map) : Cell(map, TerrainTypesEnum::Dirt)
    {
        
    }

    void Iterate() override {
    }

    void OnRain() override {
    }
};

class GravelCell : public Cell {
public:
    GravelCell(Map& map) : Cell(map, TerrainTypesEnum::Gravel)
    {
        
    }

    void Iterate() override {
        /*TODO*/
    }

    void OnRain() override {
        /*TODO*/
    }
};

class FieldCell : public Cell {
public:
    FieldCell(Map& map) : Cell(map, TerrainTypesEnum::Field)
    {
        
    }

    void Iterate() override {
        /*TODO*/
    }

    void OnRain() override {
        /*TODO*/
    }
};

class WaterCell : public Cell {
public:
    WaterCell(Map& map) : Cell(map, TerrainTypesEnum::Water)
    {
        
    }

    void Iterate() override { //add moisture to neightbor cells
        /*TODO*/
    }

};



