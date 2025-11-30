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
protected:
    Map& map_;

public:
    Terrain terrain;
    Soil soil;
    Vegetation vegetation;
    double shade;

    virtual void Iterate() { return; }
    virtual void Fertilise() { return; }
    virtual void OnRain() {return; }

    explicit Cell(Map& map, TerrainTypesEnum terrainType) :
        map_(map), terrain(terrainType), soil(0.0,0.0), vegetation(), shade(0.0) {}

};


#endif //IMS_CELL_H