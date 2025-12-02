//
// Created by tadeas on 2025-12-02.
//

#ifndef IMS_OUTPUTWINDOW_H
#define IMS_OUTPUTWINDOW_H

#include "Map.h"
#include "olcPixelGameEngine.h"
#include "Simulator.h"
#include "SpeciesEnum.h"
#include "TerrainTypesEnum.h"

class Simulator;

class OutputWindow : public olc::PixelGameEngine {
private:
    Map* map_ = nullptr;

    Simulator* simulator_ = nullptr;

    std::unordered_map<SpeciesEnum, olc::Pixel> speciesColours {
        {SpeciesEnum::Acacia, olc::Pixel(161, 116, 39, 128)},
        {SpeciesEnum::Grass, olc::Pixel(52, 207, 70, 128)},
        {SpeciesEnum::NoSpecies, olc::Pixel(0, 0, 0, 0)},
        {SpeciesEnum::Shrub, olc::Pixel(72, 194, 106, 128)},
        {SpeciesEnum::Trees, olc::Pixel(8, 94, 21, 128)}
    };

    std::unordered_map<TerrainTypesEnum, olc::Pixel> terrainColours {
        {TerrainTypesEnum::Dirt, olc::Pixel(181, 78, 0, 255)},
        {TerrainTypesEnum::Field, olc::Pixel(242, 211, 36, 255)},
        {TerrainTypesEnum::Gravel, olc::Pixel(92, 92, 89, 255)},
        {TerrainTypesEnum::Rock, olc::Pixel(23, 23, 23, 255)},
        {TerrainTypesEnum::Water, olc::Pixel(33, 152, 237, 255)}
    };

    bool OnUserCreate() override;

    bool OnUserUpdate(float fElapsedTime) override;

    void drawMap();

public:
    void init(Map* map, Simulator* simulator);

};


#endif //IMS_OUTPUTWINDOW_H