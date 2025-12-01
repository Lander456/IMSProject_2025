//
// Created by tadeas on 2025-11-27.
//

#include "../includes/Terrain.h"


char Terrain::getTerrainChar() {
    switch (type) {
        case TerrainTypesEnum::Water:
            return '~';
        case TerrainTypesEnum::Rock:
            return '.';
        case TerrainTypesEnum::Dirt:
            return ':';
        case TerrainTypesEnum::Field:
            return ';';
        case TerrainTypesEnum::Gravel:
            return '@';
    }

    return '?';
}
