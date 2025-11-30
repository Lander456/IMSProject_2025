//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

#include "Soil.h"
#include "Terrain.h"
#include "Vegetation.h"
#include "Map.h"


class Cell {
private:
    Map map_;

public:
    explicit Cell(Map& map, TerrainTypesEnum terainType) : 
        map_(map), terrain(terainType), soil(0.0,0.0), vegetation(), shade(0.0) {}


    Terrain terrain;
    Soil soil;
    Vegetation vegetation;
    double shade;

    virtual void Iterate() { return; }
    virtual void Fertilise() { return; }
    virtual void OnRain() {return; }

};


#endif //IMS_CELL_H