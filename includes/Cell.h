//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H
#include "Soil.h"
#include "Terrain.h"
#include "Vegetation.h"


class Cell {
public:
    Terrain terrain;
    Soil soil;
    Vegetation vegetation;

    Cell() : terrain(), soil(), vegetation() {}
};


#endif //IMS_CELL_H