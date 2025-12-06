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
#include "Colours.h"
#include "MapModeEnum.h"

class Simulator;

class OutputWindow : public olc::PixelGameEngine {
private:
    Map* map_ = nullptr;

    Simulator* simulator_ = nullptr;

    bool manualStepping_ = false;

    bool resetMsgShown_ = false;

    MapModes mapMode_ = MapModes::VEGETATION;

    std::unordered_map<SpeciesEnum, olc::Pixel> speciesColours {
        {SpeciesEnum::Acacia, Colours::RED},
        {SpeciesEnum::Grass, Colours::BLUE},
        {SpeciesEnum::NoSpecies, Colours::BLACK_VOID},
        {SpeciesEnum::Shrub, Colours::GREEN},
        {SpeciesEnum::Trees, Colours::WHITE}
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

    static olc::Pixel getGradientColour(olc::Pixel lowColour, olc::Pixel highColour, float normalizedVal);

public:
    void init(Map* map, Simulator* simulator, bool stepMode);

};


#endif //IMS_OUTPUTWINDOW_H