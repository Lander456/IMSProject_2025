//
// Created by tadeas on 2025-12-02.
//

#include "../includes/OutputWindow.h"
#include "../includes/Config.h"

#include <map>

class Simulator;

bool OutputWindow::OnUserCreate() {
    drawMap();
    return true;
}

bool OutputWindow::OnUserUpdate(const float fElapsedTime) {

    if (GetKey(olc::Key::SPACE).bPressed) {
        if (manualStepping_) {
            simulator_->iterate(iterationSteps_);
            
            drawMap();
            return true;
        }
    }

    if (GetKey(olc::Key::F).bPressed){
        iterationSteps_++;
        if(iterationSteps_ >= 10) iterationSteps_ = 10;
    }
    if (GetKey(olc::Key::S).bPressed){
        iterationSteps_--;
        if(iterationSteps_ <= 0) iterationSteps_ = 1;
    }

    if (GetKey(olc::Key::NP1).bPressed) iterationSteps_ = 1;

    if (GetKey(olc::Key::NP2).bPressed) iterationSteps_ = 2;

    if (GetKey(olc::Key::NP3).bPressed) iterationSteps_ = 3;

    if (GetKey(olc::Key::NP4).bPressed) iterationSteps_ = 4;

    if (GetKey(olc::Key::N).bPressed) {
        mapMode_ = MapModes::NITROGEN;

        drawMap();
        return true;
    }

    if (GetKey(olc::Key::V).bPressed) {
        mapMode_ = MapModes::VEGETATION;

        drawMap();
        return true;
    }

    if (GetKey(olc::Key::M).bPressed) {
        mapMode_ = MapModes::MOISTURE;

        drawMap();
        return true;
    }

    if (!manualStepping_) {
        static float accumulatedTime = 0.0f;
        constexpr float targetFrameTime = 1.0f / 10.0f;

        accumulatedTime += fElapsedTime;

        while (accumulatedTime >= targetFrameTime) {
            if (simulator_->generationsSimulated_ < simulator_->generationsToSim_) {
                simulator_->iterate(iterationSteps_);

                accumulatedTime -= targetFrameTime;
                drawMap();
                simulator_->generationsSimulated_++;
            } else if (!endMessageShown_) {
                endMessageShown_ = true;
                std::cout << "Simulation finished, showing final generation!" << std::endl;
            }
        }
        return true;
    }

    return true;
}

void OutputWindow::drawMap() {
    for (size_t y = 0; y < map_->getHeight(); y++) {
        for (size_t x = 0; x < map_->getWidth(); x++) {
            SetPixelMode(olc::Pixel::Mode::NORMAL);
            switch (mapMode_) {
                case MapModes::VEGETATION: {
                    auto cell = map_->at(x, y).get();
                    switch (cell->terrain.getType())
                    {
                    case TerrainTypesEnum::Dirt :
                        if(cell->vegetation->isEmpty()){
                            Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), Colours::DIRT_BROWN);
                        } else {
                            Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), speciesColours_[map_->at(x, y)->vegetation->getSpecies()]);
                        }
                        break;
                    case TerrainTypesEnum::Gravel :
                        if(cell->vegetation->isEmpty()){
                            Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), Colours::GRAVEL_GREY);
                        } else {
                            Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), speciesColours_[map_->at(x, y)->vegetation->getSpecies()]);
                        }
                        break;
                    case TerrainTypesEnum::Field :
                        Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), Colours::FIELD_YELLOW);
                        break;
                    case TerrainTypesEnum::Water :
                        Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), Colours::WATER_BLUE);
                        break;
                    case TerrainTypesEnum::Rock :
                        Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), Colours::ROCK_GREY);
                        break;
                    default:
                        Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), Colours::WHITE);
                        break;
                    }
                    break;
                }
                case MapModes::NITROGEN: {
                    const auto currentCell = map_->at(x, y).get();

                    Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), getGradientColour(Colours::WHITE, Colours::BLACK_VOID, currentCell->soil.getNitrate()/1.5));
                    break;
                }
                case MapModes::MOISTURE: {
                    const auto currentCell = map_->at(x, y).get();

                    Draw(static_cast<int32_t>(x), static_cast<int32_t>(y), getGradientColour(Colours::WHITE, Colours::WATER_BLUE, currentCell->soil.getMoisture()/100.0));
                    break;
                } 
            }
        }
    }
}

olc::Pixel OutputWindow::getGradientColour(const olc::Pixel lowColour, const olc::Pixel highColour, float normalizedVal) {

    normalizedVal = std::clamp(normalizedVal, 0.0f, 1.0f);

    const auto colour = olc::Pixel(static_cast<uint8_t>(lowColour.r + (highColour.r - lowColour.r) * normalizedVal),
        static_cast<uint8_t>(lowColour.g + (highColour.g - lowColour.g) * normalizedVal),
        static_cast<uint8_t>(lowColour.b + (highColour.b - lowColour.b) * normalizedVal),
        static_cast<uint8_t>(lowColour.a + (highColour.a - lowColour.a) * normalizedVal));

    return colour;
}

void OutputWindow::init(Map* map, Simulator* simulator, const bool stepMode) {
    map_ = map;
    simulator_ = simulator;
    manualStepping_ = stepMode;
}
