//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_CELL_H
#define IMS_CELL_H

#include "Soil.h"
#include "Terrain.h"
#include "Vegetation.h"


class Cell {
private:
    Terrain terrain_;
    Soil soil_;
    Vegetation vegetation_;
    double shade_;

public:

    [[nodiscard]] Terrain getTerrain() const { return terrain_; }
    void setTerrain(const Terrain& t) { terrain_ = t; }

    void setSoil(const Soil& soil) { soil_ = soil; }
    [[nodiscard]] Soil getSoil() const { return soil_; }

    void setVegetation(const Vegetation& v) { vegetation_ = v; }
    [[nodiscard]] Vegetation getVegetation() const { return vegetation_; }

    Cell();
};


#endif //IMS_CELL_H