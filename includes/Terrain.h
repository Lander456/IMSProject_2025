//
// Created by tadeas on 2025-11-27.
//

#ifndef IMS_TERRAIN_H
#define IMS_TERRAIN_H

#include "TerrainTypesEnum.h"


class Terrain {
private:
    TerrainTypesEnum type;

public:
    explicit Terrain(TerrainTypesEnum t) : type(t) {}

    [[nodiscard]] TerrainTypesEnum getType() const { return type; }
    [[nodiscard]] bool isHabitable() const { return type != TerrainTypesEnum::Water; }
};


#endif //IMS_TERRAIN_H