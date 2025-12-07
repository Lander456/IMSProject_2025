//
// Created by tadeas on 2025-12-04.
//

#ifndef IMS_COLOURS_H
#define IMS_COLOURS_H

#include "olcPixelGameEngine.h"

namespace Colours {

    //Vegetation colours
    static const olc::Pixel ACACIA_BROWN {161, 116, 39, 128};
    static const olc::Pixel GRASS_GREEN {52, 207, 70, 128};
    static const olc::Pixel BLACK_VOID {0, 0, 0, 255};
    static const olc::Pixel SHRUB_GREEN {72, 194, 106, 128};
    static const olc::Pixel TREE_GREEN {8, 94, 21, 128};

    //Terrain colours
    static const olc::Pixel DIRT_BROWN {161, 146, 133, 255};
    static const olc::Pixel FIELD_YELLOW {242, 211, 36, 255};
    static const olc::Pixel GRAVEL_GREY {92, 92, 89, 255};
    static const olc::Pixel ROCK_GREY {23, 23, 23, 255};
    static const olc::Pixel WATER_BLUE {33, 152, 237, 255};

    //debugging colours
    static const olc::Pixel RED {255, 0, 0, 255};
    static const olc::Pixel GREEN {0, 255, 0, 255};
    static const olc::Pixel BLUE {0, 0, 255, 255};
    static const olc::Pixel WHITE {255, 255, 255, 255};
    static const olc::Pixel YELLOW {255, 255, 0, 255};

} //Colours

#endif //IMS_COLOURS_H